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
		SwapchainInfo swapchainInfo = GetSwapchainDetails(s_GraphicsContext->m_PhysicalDevice, s_GraphicsContext->m_Surface);

		VkSurfaceFormatKHR surfaceFormat = swapchainInfo.ChooseBestSurfaceFormat();
		VkPresentModeKHR presentMode = swapchainInfo.ChooseBestPresentMode();
		VkExtent2D extent = swapchainInfo.ChooseSwapchainExtent(s_GraphicsContext->GetNativeWindow());

		uint32_t imageNum = swapchainInfo.m_SurfaceCapabilities.minImageCount + 1;

		if(swapchainInfo.m_SurfaceCapabilities.maxImageCount > 0 
			&& swapchainInfo.m_SurfaceCapabilities.maxImageCount < imageNum)
		{
			imageNum = swapchainInfo.m_SurfaceCapabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
		swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCreateInfo.surface = s_GraphicsContext->m_Surface;
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

		if(s_GraphicsContext->m_QueueFamilies.m_GraphicsFamily != s_GraphicsContext->m_QueueFamilies.m_PresentationFamily)
		{
			uint32_t familyIndices[] = {
				(uint32_t)s_GraphicsContext->m_QueueFamilies.m_GraphicsFamily,
				(uint32_t)s_GraphicsContext->m_QueueFamilies.m_PresentationFamily
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

		VkResult result = vkCreateSwapchainKHR(s_GraphicsContext->m_LogicalDevice, &swapchainCreateInfo, nullptr, &m_Swapchain);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a swapchain!");
		}

		s_GraphicsContext->m_SwapchainExtent = extent;
		s_GraphicsContext->m_SwapchainImageFormat = surfaceFormat.format;
		s_GraphicsContext->m_SwapchainColorSpace = surfaceFormat.colorSpace;
		
	}

	void VulkanFrameBuffer::CreateFrames()
	{
		uint32_t frameCount;
		vkGetSwapchainImagesKHR(s_GraphicsContext->m_LogicalDevice, m_Swapchain, &frameCount, nullptr);
		std::vector<VkImage> images(frameCount);
		vkGetSwapchainImagesKHR(s_GraphicsContext->m_LogicalDevice, m_Swapchain, &frameCount, images.data());
		
		for(VkImage image : images)
		{
			m_Frames.emplace_back(Frame(image));
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
		
	}

	void VulkanFrameBuffer::Frame::Init()
	{
		try
		{
			CreateImage();
			CreateImageView();
		}
		catch(const std::runtime_error &e)
		{
			throw e;
		}
	}

	void VulkanFrameBuffer::Frame::Shutdown()
	{
		// Destroy image views
	}

	void VulkanFrameBuffer::Frame::CreateImage()
	{
		// Add functionality later or remove completely
	}

	void VulkanFrameBuffer::Frame::CreateImageView()
	{
		VkImageViewCreateInfo imageViewCreateInfo = {};
		imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageViewCreateInfo.image = m_Image;
		imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageViewCreateInfo.format = s_GraphicsContext->m_SwapchainImageFormat;
		imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
		imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_G;
		imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
		imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
		imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		imageViewCreateInfo.subresourceRange.levelCount = 1;
		imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		imageViewCreateInfo.subresourceRange.layerCount = 1;

		VkResult result = vkCreateImageView(s_GraphicsContext->m_LogicalDevice, &imageViewCreateInfo, nullptr, &m_ImageView);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create an image view!");
		}
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
		if(e.GetEventType() == EventType::WindowResize)
		{
			RecreatePipeline();
			return true;
		}
		else
		{
			return false;
		}
	}

	bool VulkanFrameBuffer::Pipeline::BindShader(VulkanShader& shader)
	{
		if(shader.GetShaderType() == ShaderType::Vertex)
		{
			m_VertexShader = shader;
			return true;
		}
		else if(shader.GetShaderType() == ShaderType::Fragment)
		{
			m_FragmentShader = shader;
			return true;
		}
		else
		{
			return false;
		}
	}


	void VulkanFrameBuffer::Pipeline::Init()
	{
		CreatePipeline();
	}

	void VulkanFrameBuffer::Pipeline::Shutdown()
	{
		vkDestroyPipeline(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, m_Pipeline, nullptr);
		vkDestroyPipelineLayout(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, m_PipelineLayout, nullptr);
	}


	// -------------------------------------------------- Make sure to also recreate the pipeline whenever some renderer settings change, to enable dynamic settings (after implementing renderer settings)
	void VulkanFrameBuffer::Pipeline::CreatePipeline()
	{
		VkPipelineShaderStageCreateInfo shaderInfos[] = { m_VertexShader.GetCreateInfo(), m_FragmentShader.GetCreateInfo() };

		// .............................. ADD VERTEX BINDING DESCRIPTIONS AND VERTEX INPUT ....................................

		// .......................................

		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
		inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;				// Check if the restart is worth turning on

		// .............................. ADD VIEWPORT AND SCISSORS FROM THE ACTIVE CAMERA ....................................
		// Make sure to recreate the whole pipeline on window resize or camera switch!!!!!!!!!!!!
		// .......................................

		// .............................. ADD DYNAMIC STATES IF NEEDED AFTER WRITING THE SHADERS ..............................

		// .......................................

		VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
		rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
		rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
		rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;			// Make sure to modify for when creating a lvl editor
		rasterizationStateCreateInfo.lineWidth = 1.0f;
		rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;				// Check if better exists
		rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;	// Look up clockwise vs counter clockwise
		rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;


		// Check out the best multisampling settings and recreate the pipeline every time they change
		// EXPAND FUNCTIONALITY LATER
		VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
		multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
		multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;


		// Add support for choosing different blending options for interesting color driven effects
		VkPipelineColorBlendAttachmentState colorState = {};
		colorState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorState.blendEnable = VK_TRUE;
		
		colorState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorState.alphaBlendOp = VK_BLEND_OP_ADD;

		colorState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		colorState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		colorState.colorBlendOp = VK_BLEND_OP_ADD;

		VkPipelineColorBlendStateCreateInfo colorBlendCreateInfo = {};
		colorBlendCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlendCreateInfo.logicOpEnable = VK_FALSE;
		colorBlendCreateInfo.attachmentCount = 1;
		colorBlendCreateInfo.pAttachments = &colorState;

		// Make an array of descriptor set layouts;

		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		// Bind descriptor set layouts
		// Bind push constants

		VkResult result = vkCreatePipelineLayout(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, &pipelineLayoutCreateInfo, nullptr, &m_PipelineLayout);
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a pipeline layout!");
		}

		
		VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo = {};
		depthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencilStateCreateInfo.depthTestEnable = VK_TRUE;
		depthStencilStateCreateInfo.depthWriteEnable = VK_TRUE;
		depthStencilStateCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS;
		depthStencilStateCreateInfo.depthBoundsTestEnable = VK_FALSE;
		depthStencilStateCreateInfo.stencilTestEnable = VK_FALSE;

		
		VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
		pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineCreateInfo.stageCount = 2;
		pipelineCreateInfo.pStages = shaderInfos;
		// Add vertex input state
		// Add viewport and dynamic state if needed
		pipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
		pipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
		pipelineCreateInfo.pColorBlendState = &colorBlendCreateInfo;
		pipelineCreateInfo.pDepthStencilState = &depthStencilStateCreateInfo;
		pipelineCreateInfo.layout = m_PipelineLayout;
		pipelineCreateInfo.renderPass = m_RenderPass.GetNativeRenderPass();
		pipelineCreateInfo.subpass = 0;

		pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineCreateInfo.basePipelineIndex = -1;

		result = vkCreateGraphicsPipelines(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &m_Pipeline);
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a pipeline");
		}
	}


	// Implement later
	void VulkanFrameBuffer::Pipeline::RecreatePipeline()
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

	void VulkanFrameBuffer::RenderPass::Init()
	{
		
	}

	void VulkanFrameBuffer::RenderPass::Shutdown()
	{
		
	}
	
}

#endif
