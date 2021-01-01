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
	
	VulkanFrameBuffer::VulkanFrameBuffer()
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
		CreateFrames();
	}

	void VulkanFrameBuffer::Shutdown()
	{ 
		
	}

	void VulkanFrameBuffer::CreateFrames()
	{
		uint32_t frameCount;
		vkGetSwapchainImagesKHR(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), VulkanRendererAPI::GetSwapchain(), &frameCount, nullptr);
		std::vector<VkImage> images(frameCount);
		vkGetSwapchainImagesKHR(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), VulkanRendererAPI::GetSwapchain(), &frameCount, images.data());
		
		for(VkImage image : images)
		{
			Frame* frame = new Frame(image);
			m_Frames.emplace_back(frame);
		}
	}


	// ---------------- Frame -----------------

	VulkanFrameBuffer::Frame::Frame(VkImage image)
	{
		Init();
	}

	VulkanFrameBuffer::Frame::~Frame()
	{
		Shutdown();
	}

	bool VulkanFrameBuffer::Frame::OnEvent(Event& e)
	{
		return false;
	}

	void VulkanFrameBuffer::Frame::UpdateViewProjectionUniform()
	{
		ViewProjection vp;
		vp.ViewMatrix = Application::Get()->GetActiveCameraInstance()->GetViewMatrix();
		vp.ProjectionMatrix = Application::Get()->GetActiveCameraInstance()->GetProjectionMatrix();
		
		void* data;
		vkMapMemory(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), m_UniformBufferMemVP, 0, sizeof(ViewProjection), 0, &data);
		memcpy(data, &vp, sizeof(ViewProjection));
		vkUnmapMemory(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), m_UniformBufferMemVP);
	}


	void VulkanFrameBuffer::Frame::Init()
	{
		try
		{
			CreateImageView();
		}
		catch(const std::runtime_error &e)
		{
			throw e;
		}
	}

	void VulkanFrameBuffer::Frame::Shutdown()
	{
		vkDestroyFramebuffer(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), m_Framebuffer, nullptr);
	}

	void VulkanFrameBuffer::Frame::CreateImageView()
	{
		VkImageViewCreateInfo imageViewCreateInfo = {};
		imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageViewCreateInfo.image = m_Image;
		imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageViewCreateInfo.format = GR_GRAPHICS_CONTEXT->GetSwapchainImageFormat();
		imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
		imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_G;
		imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
		imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
		imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		imageViewCreateInfo.subresourceRange.levelCount = 1;
		imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		imageViewCreateInfo.subresourceRange.layerCount = 1;

		VkResult result = vkCreateImageView(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &imageViewCreateInfo, nullptr, &m_ImageView);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create an image view!");
		}
	}

	void VulkanFrameBuffer::Frame::CreateFramebuffer()
	{
		VkImageView attachments[] = { m_ImageView, s_DepthBufferImageView };

		VkFramebufferCreateInfo framebufferCreateInfo = {};
		framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCreateInfo.renderPass = VulkanRendererAPI::GetRenderPass();
		framebufferCreateInfo.attachmentCount = 1;
		framebufferCreateInfo.pAttachments = attachments;
		framebufferCreateInfo.width = GR_GRAPHICS_CONTEXT->GetSwapchainExtent().width;
		framebufferCreateInfo.height = GR_GRAPHICS_CONTEXT->GetSwapchainExtent().height;
		framebufferCreateInfo.layers = 1;

		VkResult result = vkCreateFramebuffer(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &framebufferCreateInfo, nullptr, &m_Framebuffer);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a framebuffer!");
		}
	}

	void VulkanFrameBuffer::Frame::CreateCommandBuffer()
	{
		VkCommandBufferAllocateInfo commandBufferAllocInfo = {};
		commandBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocInfo.commandPool = VulkanRendererAPI::GetGraphicsCommandPool();
		commandBufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferAllocInfo.commandBufferCount = 1;

		VkResult result = vkAllocateCommandBuffers(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &commandBufferAllocInfo, &m_CommandBuffer);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to allocate a command buffer!");
		}
	}

	void VulkanFrameBuffer::Frame::CreateUniformBuffer()
	{
		VkDeviceSize bufferSize = sizeof(ViewProjection);

		VulkanUtilities::CreateBuffer(GR_GRAPHICS_CONTEXT->GetPhysicalDevice(), GR_GRAPHICS_CONTEXT->GetLogicalDevice(), bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
										VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &m_UniformBufferVP, &m_UniformBufferMemVP);
	}

	void VulkanFrameBuffer::Frame::CreateDescriptorSet()
	{
		// Create descriptor set
		VkDescriptorSetLayout layout = VulkanRendererAPI::GetDescriptorSetLayout();
		
		VkDescriptorSetAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = VulkanRendererAPI::GetDescriptorPool();
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &layout;

		VkResult result = vkAllocateDescriptorSets(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &allocInfo, &m_DescriptorSet);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a frame descriptor set!");
		}

		// Update the descriptor set buffer bindings
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = m_UniformBufferVP;
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(ViewProjection);

		VkWriteDescriptorSet writeSet = {};
		writeSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeSet.dstSet = m_DescriptorSet;
		writeSet.dstBinding = 0;
		writeSet.dstArrayElement = 0;
		writeSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		writeSet.descriptorCount = 1;
		writeSet.pBufferInfo = &bufferInfo;

		// ADD A MATERIAL UNIFORM LATER WHEN IMPLEMENTED FOR 3D ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		vkUpdateDescriptorSets(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), 1, &writeSet, 0, nullptr);
	}


	void VulkanFrameBuffer::Frame::InitDepthTesting()
	{
		VkFormat depthBufferFormat = VulkanUtilities::ChooseSupportedFormat(GR_GRAPHICS_CONTEXT->GetPhysicalDevice(), 
			{ VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D32_SFLOAT, VK_FORMAT_D24_UNORM_S8_UINT }, 
			VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT);

		s_DepthBufferImage = VulkanUtilities::CreateImage(GR_GRAPHICS_CONTEXT->GetPhysicalDevice(), GR_GRAPHICS_CONTEXT->GetLogicalDevice(), 
			GR_GRAPHICS_CONTEXT->GetSwapchainExtent().width, GR_GRAPHICS_CONTEXT->GetSwapchainExtent().height, depthBufferFormat, VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &s_DepthBufferDeviceMemory);

		s_DepthBufferImageView = VulkanUtilities::CreateImageView(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_DepthBufferImage, depthBufferFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
	}

	void VulkanFrameBuffer::Frame::ShutdownDepthTesting()
	{
		vkDestroyImageView(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_DepthBufferImageView, nullptr);
		vkFreeMemory(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_DepthBufferDeviceMemory, nullptr);
		vkDestroyImage(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_DepthBufferImage, nullptr);
	}

	void VulkanFrameBuffer::Frame::UpdateDepthTesting()
	{
		ShutdownDepthTesting();
		InitDepthTesting();
	}

}

#endif
