#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanFrameBuffer.h"

#include "VulkanGraphicsContext.h"
#include "../../../Renderer2D/Renderer2D.h"
#include "VulkanOrthographicCamera.h"
#include "VulkanRendererAPI.h"
#include "Utils.h"

namespace Graphite
{
	
	VulkanFrameBuffer::VulkanFrameBuffer() : FrameBuffer()
	{
		Init();
	}

	VulkanFrameBuffer::~VulkanFrameBuffer()
	{
		Shutdown();
	}

	bool VulkanFrameBuffer::OnEvent(Event& e)
	{
		return false;
	}
	
	void VulkanFrameBuffer::Init()
	{
		InitDepthTesting();
		CreateFrames();
		CreateImageViews();
		CreateFramebuffers();
		CreateCommandBuffers();
		CreateUniformBuffers();
		CreateDescriptorSets();
	}

	void VulkanFrameBuffer::Shutdown()
	{ 
		
	}


	//PRETTY SURE THIS IS THE PROBLEM HERE ------------------------ RECREATE FRAMEBUFFER CLASS
	void VulkanFrameBuffer::CreateFrames()
	{
		uint32_t frameCount;
		vkGetSwapchainImagesKHR(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			VulkanRendererAPI::GetSwapchain(),
			&frameCount,
			nullptr);
		std::vector<VkImage> images(frameCount);
		vkGetSwapchainImagesKHR(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			VulkanRendererAPI::GetSwapchain(),
			&frameCount,
			images.data());
		
		for(VkImage image : images)
		{
			m_Frames.resize(0);
			Frame f;
			f.Image = image;
			m_Frames.emplace_back(f);
		}
		
	}

	void VulkanFrameBuffer::CreateFramebuffers()
	{
		for(Frame& f : m_Frames)
		{
			VkImageView attachments[] = { f.ImageView, m_DepthBufferImageView };

			VkFramebufferCreateInfo framebufferCreateInfo = {};
			framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferCreateInfo.renderPass = VulkanRendererAPI::GetRenderPass();
			framebufferCreateInfo.attachmentCount = 1;
			framebufferCreateInfo.pAttachments = attachments;
			framebufferCreateInfo.width = GR_GRAPHICS_CONTEXT->GetSwapchainExtent().width;
			framebufferCreateInfo.height = GR_GRAPHICS_CONTEXT->GetSwapchainExtent().height;
			framebufferCreateInfo.layers = 1;

			VkResult result = vkCreateFramebuffer(
				GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
				&framebufferCreateInfo,
				nullptr,
				&f.Framebuffer);

			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create a framebuffer!");
			}
		}
	}
	
	void VulkanFrameBuffer::CreateCommandBuffers()
	{
		for (Frame& f : m_Frames)
		{
			VkCommandBufferAllocateInfo commandBufferAllocInfo = {};
			commandBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			commandBufferAllocInfo.commandPool = VulkanRendererAPI::GetGraphicsCommandPool();
			commandBufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			commandBufferAllocInfo.commandBufferCount = 1;

			VkResult result = vkAllocateCommandBuffers(
				GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
				&commandBufferAllocInfo,
				&f.CommandBuffer);

			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to allocate a command buffer!");
			}
		}
	}
	
	void VulkanFrameBuffer::CreateUniformBuffers()
	{
		for (Frame& f : m_Frames)
		{
			VkDeviceSize bufferSize = sizeof(ViewProjection);

			VulkanUtilities::CreateBuffer(
				GR_GRAPHICS_CONTEXT->GetPhysicalDevice(),
				GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
				bufferSize,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				&f.UniformBufferVP,
				&f.UniformBufferMemVP);
		}
	}
	
	void VulkanFrameBuffer::UpdateViewProjectionUniform(uint32_t currentFrame)
	{
		ViewProjection vp;
		vp.ViewMatrix = Application::Get()->GetActiveCameraInstance()->GetViewMatrix();
		vp.ProjectionMatrix = Application::Get()->GetActiveCameraInstance()->GetProjectionMatrix();
		
		void* data;
		vkMapMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_Frames[currentFrame].UniformBufferMemVP,
			0,
			sizeof(ViewProjection),
			0,
			&data);
		memcpy(
			data,
			&vp,
			sizeof(ViewProjection));
		vkUnmapMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_Frames[currentFrame].UniformBufferMemVP);
	}


	void VulkanFrameBuffer::CreateImageViews()
	{
		for(Frame& f : m_Frames)
		{
			f.ImageView = VulkanUtilities::CreateImageView(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), f.Image, VulkanRendererAPI::GetSwapchainSurfaceFormat().format, VK_IMAGE_ASPECT_COLOR_BIT);
		}
	}
	
	void VulkanFrameBuffer::CreateDescriptorSets()
	{
		for(Frame& f : m_Frames)
		{
			// Create descriptor set
			VkDescriptorSetLayout layout = VulkanRendererAPI::GetDescriptorSetLayout();

			VkDescriptorSetAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			allocInfo.descriptorPool = VulkanRendererAPI::GetDescriptorPool();
			allocInfo.descriptorSetCount = 1;
			allocInfo.pSetLayouts = &layout;

			VkResult result = vkAllocateDescriptorSets(
				GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
				&allocInfo,
				&f.DescriptorSet);

			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create a frame descriptor set!");
			}

			// Update the descriptor set buffer bindings
			VkDescriptorBufferInfo bufferInfo = {};
			bufferInfo.buffer = f.UniformBufferVP;
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(ViewProjection);

			VkWriteDescriptorSet writeSet = {};
			writeSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			writeSet.dstSet = f.DescriptorSet;
			writeSet.dstBinding = 0;
			writeSet.dstArrayElement = 0;
			writeSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			writeSet.descriptorCount = 1;
			writeSet.pBufferInfo = &bufferInfo;

			// ADD A MATERIAL UNIFORM LATER WHEN IMPLEMENTED FOR 3D ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			vkUpdateDescriptorSets(
				GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
				1,
				&writeSet,
				0,
				nullptr);
		}
	}


	void VulkanFrameBuffer::InitDepthTesting()
	{
		VkFormat depthBufferFormat = VulkanUtilities::ChooseSupportedFormat(
			GR_GRAPHICS_CONTEXT->GetPhysicalDevice(), 
			{ VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D32_SFLOAT, VK_FORMAT_D24_UNORM_S8_UINT }, 
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);

		m_DepthBufferImage = VulkanUtilities::CreateImage(
			GR_GRAPHICS_CONTEXT->GetPhysicalDevice(),
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(), 
			GR_GRAPHICS_CONTEXT->GetSwapchainExtent().width,
			GR_GRAPHICS_CONTEXT->GetSwapchainExtent().height,
			depthBufferFormat,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			&m_DepthBufferDeviceMemory);
		
		m_DepthBufferImageView = VulkanUtilities::CreateImageView(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_DepthBufferImage,
			depthBufferFormat,
			VK_IMAGE_ASPECT_DEPTH_BIT);
			
	}

	void VulkanFrameBuffer::ShutdownDepthTesting()
	{
		vkDestroyImageView(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_DepthBufferImageView,
			nullptr);
		vkFreeMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_DepthBufferDeviceMemory,
			nullptr);
		vkDestroyImage(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_DepthBufferImage,
			nullptr);
	}

	void VulkanFrameBuffer::UpdateDepthTesting()
	{
		ShutdownDepthTesting();
		InitDepthTesting();
	}

}

#endif
