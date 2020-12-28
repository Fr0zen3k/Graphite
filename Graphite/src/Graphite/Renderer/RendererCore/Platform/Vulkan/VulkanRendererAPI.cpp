#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanRendererAPI.h"
#include "VulkanOrthographicCamera.h"
#include "VulkanPerspectiveCamera.h"
#include "../../Camera.h"

namespace Graphite
{
	void VulkanRendererAPI::Init()
	{
		CreateSwapchain();
		CreateCommandPool();
		CreateRenderPass();
		CreateSwapchain();
	}

	void VulkanRendererAPI::Shutdown()
	{
		
	}

	bool VulkanRendererAPI::OnEvent(const Event& e)
	{
		
	}

	bool VulkanRendererAPI::BindShader(VulkanShader* shader)
	{
		if (shader->GetShaderType() == ShaderType::Vertex)
		{
			s_VertexShader = shader;
			return true;
		}
		else if (shader->GetShaderType() == ShaderType::Fragment)
		{
			s_FragmentShader = shader;
			return true;
		}
		else
		{
			return false;
		}
	}


	void VulkanRendererAPI::CreateSwapchain()
	{
		VulkanUtilities::SwapchainInfo swapchainInfo = VulkanUtilities::GetSwapchainDetails(GR_GRAPHICS_CONTEXT->GetPhysicalDevice(), GR_GRAPHICS_CONTEXT->GetSurface());

		VkSurfaceFormatKHR surfaceFormat = swapchainInfo.ChooseBestSurfaceFormat();
		VkPresentModeKHR presentMode = swapchainInfo.ChooseBestPresentMode();
		VkExtent2D extent = swapchainInfo.ChooseSwapchainExtent(GR_GRAPHICS_CONTEXT->GetNativeWindow());

		uint32_t imageNum = swapchainInfo.m_SurfaceCapabilities.minImageCount + 1;

		if (swapchainInfo.m_SurfaceCapabilities.maxImageCount > 0
			&& swapchainInfo.m_SurfaceCapabilities.maxImageCount < imageNum)
		{
			imageNum = swapchainInfo.m_SurfaceCapabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
		swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCreateInfo.surface = GR_GRAPHICS_CONTEXT->GetSurface();
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

		if (GR_GRAPHICS_CONTEXT->GetQueueFamiliesIndices().GraphicsFamily != GR_GRAPHICS_CONTEXT->GetQueueFamiliesIndices().PresentationFamily)
		{
			uint32_t familyIndices[] = {
				(uint32_t)GR_GRAPHICS_CONTEXT->GetQueueFamiliesIndices().GraphicsFamily,
				(uint32_t)GR_GRAPHICS_CONTEXT->GetQueueFamiliesIndices().PresentationFamily
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

		VkResult result = vkCreateSwapchainKHR(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &swapchainCreateInfo, nullptr, &s_Swapchain);

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a swapchain!");
		}

		GR_GRAPHICS_CONTEXT->SetSwapchainExtent(extent);
		GR_GRAPHICS_CONTEXT->SetSwapchainImageFormat(surfaceFormat.format);
		GR_GRAPHICS_CONTEXT->SetSwapchainColorSpace(surfaceFormat.colorSpace);

	}

	void VulkanRendererAPI::CreateRenderPass()
	{
		VkAttachmentDescription colorAttachment = {};
		colorAttachment.format = GR_GRAPHICS_CONTEXT->GetSwapchainImageFormat();
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		// Add depth description later

		// Add subpasses if necessary when adding multiple subpass support

		VkAttachmentReference colorRef = {};
		colorRef.attachment = 0;
		colorRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorRef;

		VkRenderPassCreateInfo renderPassCreateInfo = {};
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCreateInfo.attachmentCount = 1;
		renderPassCreateInfo.pAttachments = &colorAttachment;
		renderPassCreateInfo.subpassCount = 1;
		renderPassCreateInfo.pSubpasses = &subpass;

		VkResult result = vkCreateRenderPass(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &renderPassCreateInfo, nullptr, &s_RenderPass);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a render pass!");
		}
	}

	void VulkanRendererAPI::CreateGraphicsPipeline()
	{
		VkPipelineShaderStageCreateInfo shaderInfos[] = { s_VertexShader->GetCreateInfo(), s_FragmentShader->GetCreateInfo() };

		// .............................. ADD VERTEX BINDING DESCRIPTIONS AND VERTEX INPUT ....................................

		// .......................................

		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
		inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;				// Check if the restart is worth turning on

		// .............................. ADD VIEWPORT AND SCISSORS FROM THE ACTIVE CAMERA ....................................
		VkViewport viewport;
		VkRect2D scissors;
		Camera* camera = Application::Get()->GetActiveCameraInstance();

		if (camera->GetCameraType() == CameraType::Orthographic)
		{
			viewport = dynamic_cast<VulkanOrthographicCamera*>(camera)->GetViewport();
			scissors = dynamic_cast<VulkanOrthographicCamera*>(camera)->GetScissors();
		}
		else if (camera->GetCameraType() == CameraType::Perspective)
		{
			viewport = dynamic_cast<VulkanPerspectiveCamera*>(camera)->GetViewport();
			scissors = dynamic_cast<VulkanPerspectiveCamera*>(camera)->GetScissors();
		}

		VkPipelineViewportStateCreateInfo  viewportInfo = {};
		viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportInfo.viewportCount = 1;
		viewportInfo.pViewports = &viewport;
		viewportInfo.scissorCount = 1;
		viewportInfo.pScissors = &scissors;

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

		VkResult result = vkCreatePipelineLayout(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &pipelineLayoutCreateInfo, nullptr, &s_GraphicsPipelineLayout);
		if (result != VK_SUCCESS)
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
		pipelineCreateInfo.pViewportState = &viewportInfo;
		pipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
		pipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
		pipelineCreateInfo.pColorBlendState = &colorBlendCreateInfo;
		pipelineCreateInfo.pDepthStencilState = &depthStencilStateCreateInfo;
		pipelineCreateInfo.layout = s_GraphicsPipelineLayout;
		pipelineCreateInfo.renderPass = s_RenderPass;
		pipelineCreateInfo.subpass = 0;

		pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineCreateInfo.basePipelineIndex = -1;

		result = vkCreateGraphicsPipelines(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &s_GraphicsPipeline);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a pipeline");
		}
	}

	void VulkanRendererAPI::RecreateGraphicsPipeline()
	{
		
	}


	void VulkanRendererAPI::CreateCommandPool()
	{
		VkCommandPoolCreateInfo commandPoolCreateInfo = {};
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.queueFamilyIndex = GR_GRAPHICS_CONTEXT->GetQueueFamiliesIndices().GraphicsFamily;
		commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		VkResult result = vkCreateCommandPool(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &commandPoolCreateInfo, nullptr, &s_GraphicsCommandPool);

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a command pool!");
		}
	}

	void VulkanRendererAPI::CreateDescriptorPools()
	{
		VkDescriptorPoolSize vpPoolSize = {};
		vpPoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		vpPoolSize.descriptorCount = static_cast<uint32_t>(s_FrameBuffer->Size());

		std::vector<VkDescriptorPoolSize> poolSizes = { vpPoolSize };

		VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {};
		descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorPoolCreateInfo.maxSets = static_cast<uint32_t>(s_FrameBuffer->Size());
		descriptorPoolCreateInfo.maxSets = static_cast<uint32_t>(poolSizes.size());
		descriptorPoolCreateInfo.pPoolSizes = poolSizes.data();

		VkResult result = vkCreateDescriptorPool(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &descriptorPoolCreateInfo, nullptr, &s_DescriptorPool);
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a descriptor set pool!");
		}

		VkDescriptorPoolSize samplerPoolSize = {};
		vpPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		vpPoolSize.descriptorCount = static_cast<uint32_t>(s_FrameBuffer->Size());

		VkDescriptorPoolCreateInfo samplerDescriptorPoolCreateInfo = {};
		samplerDescriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		samplerDescriptorPoolCreateInfo.maxSets = MAX_OBJECTS;
		samplerDescriptorPoolCreateInfo.maxSets = 1;
		samplerDescriptorPoolCreateInfo.pPoolSizes = &samplerPoolSize;

		vkCreateDescriptorPool(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &samplerDescriptorPoolCreateInfo, nullptr, &s_SamplerDescriptorPool);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a descriptor set pool!");
		}
	}

	void VulkanRendererAPI::CreatePushConstantRange()
	{
		s_PushConstantRange = {};
		s_PushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		s_PushConstantRange.offset = 0;
		s_PushConstantRange.size = sizeof(glm::mat4);
	}

	void VulkanRendererAPI::CreateSynchronisation()
	{
		s_ImageAvailableSemaphores.resize(MAX_FRAME_DRAWS);
		s_RenderFinishSemaphores.resize(MAX_FRAME_DRAWS);
		s_DrawFences.resize(MAX_FRAME_DRAWS);

		VkSemaphoreCreateInfo semInfo = {};
		semInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo = {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for(int i = 0; i < MAX_FRAME_DRAWS; i++)
		{
			if(vkCreateSemaphore(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &semInfo, nullptr, &s_ImageAvailableSemaphores[i]) != VK_SUCCESS || 
				vkCreateSemaphore(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &semInfo, nullptr, &s_RenderFinishSemaphores[i]))
			{
				throw std::runtime_error("Failed to create a semaphore!");
			}

			if(vkCreateFence(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &fenceInfo, nullptr, &s_DrawFences[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create a fence!");
			}
		}
	}

}

#endif
