#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN


#include "VulkanFrameBuffer.h"

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
		
	}

	void VulkanFrameBuffer::Init()
	{
		CreateSwapchain();
		CreateFrames();
	}

	void VulkanFrameBuffer::Shutdown()
	{
		
	}

	void VulkanFrameBuffer::CreateSwapchain()
	{
		SwapchainInfo swapchainInfo = GetSwapchainDetails(m_GraphicsContext->m_PhysicalDevice, m_GraphicsContext->m_Surface);

		VkSurfaceFormatKHR surfaceFormat = swapchainInfo.ChooseBestSurfaceFormat();
		VkPresentModeKHR presentMode = swapchainInfo.ChooseBestPresentMode();
		VkExtent2D extent = swapchainInfo.ChooseSwapchainExtent(m_GraphicsContext->GetNativeWindow());

		uint32_t imageNum = swapchainInfo.m_SurfaceCapabilities.minImageCount + 1;

		if(swapchainInfo.m_SurfaceCapabilities.maxImageCount > 0 
			&& swapchainInfo.m_SurfaceCapabilities.maxImageCount < imageNum)
		{
			imageNum = swapchainInfo.m_SurfaceCapabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
		swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCreateInfo.surface = m_GraphicsContext->m_Surface;
		swapchainCreateInfo.imageFormat = surfaceFormat.format;
		swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
		swapchainCreateInfo.presentMode = presentMode;
		swapchainCreateInfo.imageExtent = extent;
		swapchainCreateInfo.minImageCount = imageNum;
		swapchainCreateInfo.imageArrayLayers = 1;
		swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainCreateInfo.preTransform = swapchainInfo.m_SurfaceCapabilities.currentTransform;
		swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchainCreateInfo.clipped = VK_TRUE;

		if(m_GraphicsContext->m_QueueFamilies.m_GraphicsFamily != m_GraphicsContext->m_QueueFamilies.m_PresentationFamily)
		{
			uint32_t familyIndices[] = {
				(uint32_t)m_GraphicsContext->m_QueueFamilies.m_GraphicsFamily,
				(uint32_t)m_GraphicsContext->m_QueueFamilies.m_PresentationFamily
			};

			swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			swapchainCreateInfo.queueFamilyIndexCount = 2;
			swapchainCreateInfo.pQueueFamilyIndices = familyIndices;
		}
		else
		{
			swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			swapchainCreateInfo.queueFamilyIndexCount = 0;
			swapchainCreateInfo.pQueueFamilyIndices = nullptr;
		}

		swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

		VkResult result = vkCreateSwapchainKHR(m_GraphicsContext->m_LogicalDevice, &swapchainCreateInfo, nullptr, &m_Swapchain);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a swapchain!");
		}

		m_GraphicsContext->m_SwapchainExtent = extent;
		m_GraphicsContext->m_SwapchainImageFormat = surfaceFormat.format;
		m_GraphicsContext->m_SwapchainColorSpace = surfaceFormat.colorSpace;
		
	}

	void VulkanFrameBuffer::CreateFrames()
	{
		uint32_t frameCount;
		vkGetSwapchainImagesKHR(m_GraphicsContext->m_LogicalDevice, m_Swapchain, &frameCount, nullptr);
		std::vector<VkImage> images(frameCount);
		vkGetSwapchainImagesKHR(m_GraphicsContext->m_LogicalDevice, m_Swapchain, &frameCount, images.data());
		
		for(VkImage image : images)
		{
			Frame frame;
			frame.m_Image = image;
			frame.m_ImageView; // create the image view

			m_Frames.push_back(frame);
		}
	}

	// ---------------- Frame -----------------

	VulkanFrameBuffer::Frame::Frame()
	{
		Init();
	}

	VulkanFrameBuffer::Frame::~Frame()
	{
		Shutdown();
	}

	bool VulkanFrameBuffer::Frame::OnEvent(Event& e)
	{
		
	}

	void VulkanFrameBuffer::Frame::Init()
	{
		
	}

	void VulkanFrameBuffer::Frame::Shutdown()
	{
		
	}

	void VulkanFrameBuffer::Frame::CreateImage()
	{
		
	}

	void VulkanFrameBuffer::Frame::CreateColorImage()
	{
		
	}

	void VulkanFrameBuffer::Frame::CreateDepthBufferImage()
	{
		
	}

	void VulkanFrameBuffer::Frame::CreateSynchronisation()
	{
		
	}

	// ------------------- Pipeline ---------------------

	VulkanFrameBuffer::Pipeline::Pipeline()
	{
		Init();
	}

	VulkanFrameBuffer::Pipeline::~Pipeline()
	{
		Shutdown();
	}

	bool VulkanFrameBuffer::Pipeline::OnEvent(Event& e)
	{
		
	}

	void VulkanFrameBuffer::Pipeline::Init()
	{
		
	}

	void VulkanFrameBuffer::Pipeline::Shutdown()
	{
		
	}

	void VulkanFrameBuffer::Pipeline::CreatePipeline()
	{
		
	}

	// --------------- Render Pass ---------------------

	VulkanFrameBuffer::RenderPass::RenderPass()
	{
		
	}

	VulkanFrameBuffer::RenderPass::~RenderPass()
	{
		
	}

	bool VulkanFrameBuffer::RenderPass::OnEvent(Event& e)
	{
		
	}

	bool VulkanFrameBuffer::RenderPass::BindPipeline(const Pipeline& pipeline)
	{
		
	}

	void VulkanFrameBuffer::RenderPass::Init()
	{
		
	}

	void VulkanFrameBuffer::RenderPass::Shutdown()
	{
		
	}
	
}

#endif
