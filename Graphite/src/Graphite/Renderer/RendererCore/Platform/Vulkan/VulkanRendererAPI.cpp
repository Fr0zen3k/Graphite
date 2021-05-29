#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanRendererAPI.h"
#include "VulkanOrthographicCamera.h"
#include "VulkanPerspectiveCamera.h"
#include "../../Camera.h"
#include "VulkanGraphicsContext.h"
#include "../../../Renderer3D/Renderer3D.h"
#include "VulkanIndexBuffer.h"
#include "VulkanTexture.h"
#include "VulkanVertexBuffer.h"

namespace Graphite
{
	uint8_t VulkanRendererAPI::s_CurrentFrame = 0;

	VulkanFrameBuffer* VulkanRendererAPI::s_FrameBuffer;

	VkSwapchainKHR VulkanRendererAPI::s_Swapchain;

	VkSurfaceFormatKHR VulkanRendererAPI::s_SwapchainSurfaceFormat;

	VkRenderPass VulkanRendererAPI::s_RenderPass;

	VkPipeline VulkanRendererAPI::s_GraphicsPipeline;
	VkPipelineLayout VulkanRendererAPI::s_GraphicsPipelineLayout = {};

	VulkanShader* VulkanRendererAPI::s_VertexShader;
	VulkanShader* VulkanRendererAPI::s_FragmentShader;

	VkCommandPool VulkanRendererAPI::s_GraphicsCommandPool;

	VkDescriptorPool VulkanRendererAPI::s_DescriptorPool;
	VkDescriptorPool VulkanRendererAPI::s_SamplerDescriptorPool;

	VkDescriptorSetLayout VulkanRendererAPI::s_DescriptorSetLayout;
	VkDescriptorSetLayout VulkanRendererAPI::s_SamplerDescriptorSetLayout;

	VkPushConstantRange VulkanRendererAPI::s_PushConstantRange;

	std::vector<VkSemaphore> VulkanRendererAPI::s_ImageAvailableSemaphores;
	std::vector<VkSemaphore> VulkanRendererAPI::s_RenderFinishSemaphores;
	std::vector<VkFence> VulkanRendererAPI::s_DrawFences;
	
	void VulkanRendererAPI::Init()
	{
		try
		{
			s_FragmentShader = new VulkanShader(ShaderType::Fragment, "./Shaders/frag.spv");
			s_VertexShader = new VulkanShader(ShaderType::Vertex, "./Shaders/vert.spv");
			CreateSwapchain();
			CreatePushConstantRange();
			CreateCommandPool();
			VulkanTexture::CreateCommonSampler();
			CreateDescriptorSetLayouts();
			CreateRenderPass();
			s_FrameBuffer = new VulkanFrameBuffer();
			CreateDescriptorPools();
			s_FrameBuffer->CreateDescriptorSets();
			CreateGraphicsPipeline();
			CreateSynchronisation();
			
		}
		catch (const std::runtime_error& e)
		{
			throw e;
		}
	}

	void VulkanRendererAPI::Shutdown()
	{
		vkDeviceWaitIdle(GR_GRAPHICS_CONTEXT->GetLogicalDevice());

		for(int i = 0; i < MAX_FRAME_DRAWS; i++)
		{
			vkDestroySemaphore(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_ImageAvailableSemaphores[i], nullptr);
			vkDestroySemaphore(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_RenderFinishSemaphores[i], nullptr);
			vkDestroyFence(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_DrawFences[i], nullptr);
		}

		vkDestroyDescriptorSetLayout(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_DescriptorSetLayout, nullptr);
		vkDestroyDescriptorSetLayout(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_SamplerDescriptorSetLayout, nullptr);

		vkDestroyDescriptorPool(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_DescriptorPool, nullptr);
		vkDestroyDescriptorPool(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_SamplerDescriptorPool, nullptr);

		delete s_FrameBuffer;
		delete s_FragmentShader;
		delete s_VertexShader;

		vkDestroyCommandPool(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_GraphicsCommandPool, nullptr);

		vkDestroyPipeline(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_GraphicsPipeline, nullptr);
		vkDestroyPipelineLayout(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_GraphicsPipelineLayout, nullptr);

		vkDestroyRenderPass(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_RenderPass, nullptr);
		vkDestroySwapchainKHR(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), s_Swapchain, nullptr);
	}

	bool VulkanRendererAPI::OnEvent(const Event& e)
	{
		return false;
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

	uint32_t VulkanRendererAPI::StartDrawing()
	{
		vkWaitForFences(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(), 
			1, &s_DrawFences[s_CurrentFrame], 
			VK_TRUE, 
			std::numeric_limits<uint64_t>::max());

		vkResetFences(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			1,
			&s_DrawFences[s_CurrentFrame]);

		uint32_t imageIndex;
		vkAcquireNextImageKHR(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			s_Swapchain,
			std::numeric_limits<uint64_t>::max(),
			s_ImageAvailableSemaphores[s_CurrentFrame],
			VK_NULL_HANDLE,
			&imageIndex);

		return imageIndex;
	}

	// Recording the commands for the data given for drawing
	void VulkanRendererAPI::Draw(uint32_t imageIndex, VulkanVertexBuffer* pVertexBuffer, VulkanIndexBuffer* pIndexBuffer, VulkanTexture* pTexture, const glm::mat4& modelMatrix, const Material& material)
	{
		Application::Get()->GetActiveCameraInstance()->Translate(glm::vec3(-1.0f, -1.0f, -1.0f));
		
		s_FrameBuffer->UpdateViewProjectionUniform(imageIndex);
		
		VkCommandBufferBeginInfo commandBufferBeginInfo = {};
		commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		VkRenderPassBeginInfo renderPassBeginInfo = {};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassBeginInfo.renderPass = s_RenderPass;
		renderPassBeginInfo.renderArea.offset = { 0, 0 };
		renderPassBeginInfo.renderArea.extent = GR_GRAPHICS_CONTEXT->GetSwapchainExtent();

		std::array<VkClearValue, 2> clearValues = {};
		clearValues[0].color = { 0.6f, 0.65f, 0.4f, 1.0f };										//{0.24f, 0.23f, 0.24f, 1.0f};
		clearValues[1].depthStencil.depth = 1.0f;

		renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassBeginInfo.pClearValues = clearValues.data();
		renderPassBeginInfo.framebuffer = s_FrameBuffer->GetFrame(imageIndex).Framebuffer;

		VkResult result = vkBeginCommandBuffer(
			s_FrameBuffer->GetFrame(imageIndex).CommandBuffer,
			&commandBufferBeginInfo);
		
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to start recording a command buffer!");
		}


		// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ BEGIN RENDER PASS $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

		
			vkCmdBeginRenderPass(
				s_FrameBuffer->GetFrame(imageIndex).CommandBuffer,
				&renderPassBeginInfo, 
				VK_SUBPASS_CONTENTS_INLINE);

			
				vkCmdBindPipeline(
					s_FrameBuffer->GetFrame(imageIndex).CommandBuffer,
					VK_PIPELINE_BIND_POINT_GRAPHICS,
					s_GraphicsPipeline);

				VkViewport viewport = {};
				viewport.x = 0.0f;
				viewport.y = 0.0f;
				viewport.width = (float)GR_GRAPHICS_CONTEXT->GetFrameSize().first;
				viewport.height = (float)GR_GRAPHICS_CONTEXT->GetFrameSize().second;
				viewport.minDepth = 0.0f;
				viewport.maxDepth = 1.0f;

				vkCmdSetViewport(
					s_FrameBuffer->GetFrame(imageIndex).CommandBuffer,
					0,
					1,
					&viewport);

				VkRect2D scissors = {};
				scissors.offset = { 0, 0 };
				scissors.extent = GR_GRAPHICS_CONTEXT->GetSwapchainExtent();

				vkCmdSetScissor(
					s_FrameBuffer->GetFrame(imageIndex).CommandBuffer,
					0,
					1,
					&scissors);

				// Data binding
				if(pVertexBuffer != nullptr && pIndexBuffer != nullptr && pTexture != nullptr)
				{
					VkBuffer vertexBuffers[] = { pVertexBuffer->GetNativeBuffer() };
					VkDeviceSize offsets[] = { 0 };

					vkCmdBindVertexBuffers(s_FrameBuffer->GetFrame(imageIndex).CommandBuffer, 0, 1, vertexBuffers, offsets);

					vkCmdBindIndexBuffer(s_FrameBuffer->GetFrame(imageIndex).CommandBuffer, pIndexBuffer->GetNativeBuffer(), 0, VK_INDEX_TYPE_UINT32);

					glm::mat4 view = Application::Get()->GetActiveCameraInstance()->GetViewMatrix();
					
					glm::mat4 normalMatrix = glm::transpose(glm::inverse(view * modelMatrix));
					
					VulkanUtilities::PushConstantsData data;

					data.model = modelMatrix;
					data.normal = normalMatrix;
					data.ambient = glm::vec4(material.GetAmbient(), 1.0f);
					data.specular = glm::vec4(material.GetSpecular(), 1.0f);
					data.light = view * modelMatrix * glm::vec4(material.GetLight(), 1.0f);
					data.phongData = glm::vec4(material.GetKa(), material.GetKd(), material.GetKs(), material.GetShininess());

					vkCmdPushConstants(
						s_FrameBuffer->GetFrame(imageIndex).CommandBuffer,
						s_GraphicsPipelineLayout,
						VK_SHADER_STAGE_ALL_GRAPHICS,
						0,
						sizeof(VulkanUtilities::PushConstantsData),
						&data);

					std::array<VkDescriptorSet, 2> descriptorSets = { s_FrameBuffer->GetFrame(imageIndex).DescriptorSet, pTexture->GetDescriptorSet() };

					vkCmdBindDescriptorSets(
						s_FrameBuffer->GetFrame(imageIndex).CommandBuffer, 
						VK_PIPELINE_BIND_POINT_GRAPHICS, 
						s_GraphicsPipelineLayout, 
						0, 
						static_cast<uint32_t>(descriptorSets.size()), 
						descriptorSets.data(), 
						0, 
						nullptr);

					vkCmdDrawIndexed(s_FrameBuffer->GetFrame(imageIndex).CommandBuffer, pIndexBuffer->Size(), 1, 0, 0, 0);
				}

			vkCmdEndRenderPass(s_FrameBuffer->GetFrame(imageIndex).CommandBuffer);
		

		// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ END RENDER PASS $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


		result = vkEndCommandBuffer(s_FrameBuffer->GetFrame(imageIndex).CommandBuffer);
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to stop recording a command buffer!");
		}
	}

	void VulkanRendererAPI::EndDrawing(uint32_t imageIndex)
	{
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &s_ImageAvailableSemaphores[s_CurrentFrame];
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &s_FrameBuffer->GetFrame(imageIndex).CommandBuffer;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &s_RenderFinishSemaphores[s_CurrentFrame];

		VkResult result = vkQueueSubmit(
			GR_GRAPHICS_CONTEXT->GetGraphicsQueue(),
			1,
			&submitInfo,
			s_DrawFences[s_CurrentFrame]);
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to submit a commang buffer to the graphics queue!");
		}

		// Present the image to screen
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &s_RenderFinishSemaphores[s_CurrentFrame];
		presentInfo.pSwapchains = &s_Swapchain;
		presentInfo.swapchainCount = 1;
		presentInfo.pImageIndices = &imageIndex;
		
		result = vkQueuePresentKHR(
			GR_GRAPHICS_CONTEXT->GetPresentationQueue(),
			&presentInfo);
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to present an image to the screen!");
		}

		s_CurrentFrame = (s_CurrentFrame + 1) % MAX_FRAME_DRAWS;
	}
	

	void VulkanRendererAPI::CreateSwapchain()
	{
		VulkanUtilities::SwapchainInfo swapchainInfo = VulkanUtilities::GetSwapchainDetails(
			GR_GRAPHICS_CONTEXT->GetPhysicalDevice(),
			GR_GRAPHICS_CONTEXT->GetSurface());

		s_SwapchainSurfaceFormat = swapchainInfo.ChooseBestSurfaceFormat();
		VkPresentModeKHR presentMode = swapchainInfo.ChooseBestPresentMode();
		VkExtent2D extent = swapchainInfo.ChooseSwapchainExtent(GR_GRAPHICS_CONTEXT->GetNativeWindow());
		GR_GRAPHICS_CONTEXT->SetSwapchainExtent(extent);

		uint32_t imageNum = swapchainInfo.m_SurfaceCapabilities.minImageCount + 1;

		if (swapchainInfo.m_SurfaceCapabilities.maxImageCount > 0
			&& swapchainInfo.m_SurfaceCapabilities.maxImageCount < imageNum)
		{
			imageNum = swapchainInfo.m_SurfaceCapabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
		swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCreateInfo.surface = GR_GRAPHICS_CONTEXT->GetSurface();
		swapchainCreateInfo.imageFormat = s_SwapchainSurfaceFormat.format;
		swapchainCreateInfo.imageColorSpace = s_SwapchainSurfaceFormat.colorSpace;
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

		VkResult result = vkCreateSwapchainKHR(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&swapchainCreateInfo,
			nullptr,
			&s_Swapchain);

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a swapchain!");
		}

		GR_GRAPHICS_CONTEXT->SetSwapchainExtent(extent);
		GR_GRAPHICS_CONTEXT->SetSwapchainImageFormat(s_SwapchainSurfaceFormat.format);
		GR_GRAPHICS_CONTEXT->SetSwapchainColorSpace(s_SwapchainSurfaceFormat.colorSpace);

	}

	void VulkanRendererAPI::CreateRenderPass()
	{
		VkAttachmentDescription colorAttachment = {};
		colorAttachment.format = GR_GRAPHICS_CONTEXT->GetSwapchainImageFormat();
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;					// VK_ATTACHMENT_STORE_OP_DONT_CARE
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentDescription depthAttachment = {};
		depthAttachment.format = VulkanUtilities::ChooseSupportedFormat(
			GR_GRAPHICS_CONTEXT->GetPhysicalDevice(),
			{ VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D32_SFLOAT, VK_FORMAT_D24_UNORM_S8_UINT },
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
		depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentReference colorRef = {};
		colorRef.attachment = 0;
		colorRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depthRef = {};
		depthRef.attachment = 1;
		depthRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorRef;
		subpass.pDepthStencilAttachment = &depthRef;

		std::array<VkSubpassDependency, 2> subpassDependencies;

		subpassDependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
		subpassDependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		subpassDependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		subpassDependencies[0].dstSubpass = 0;
		subpassDependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		subpassDependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		subpassDependencies[0].dependencyFlags = 0;

		subpassDependencies[1].srcSubpass = 0;
		subpassDependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		subpassDependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;;
		subpassDependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
		subpassDependencies[1].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		subpassDependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		subpassDependencies[1].dependencyFlags = 0;

		std::array<VkAttachmentDescription, 2> renderPassAttachments = { colorAttachment, depthAttachment };

		VkRenderPassCreateInfo renderPassCreateInfo = {};
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(renderPassAttachments.size());
		renderPassCreateInfo.pAttachments = renderPassAttachments.data();
		renderPassCreateInfo.dependencyCount = static_cast<uint32_t>(subpassDependencies.size());
		renderPassCreateInfo.pDependencies = subpassDependencies.data();
		renderPassCreateInfo.subpassCount = 1;
		renderPassCreateInfo.pSubpasses = &subpass;

		VkResult result = vkCreateRenderPass(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&renderPassCreateInfo,
			nullptr,
			&s_RenderPass);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a render pass!");
		}
	}

	void VulkanRendererAPI::CreateGraphicsPipeline()
	{
		//D:/Graphite/Graphite/src/Graphite/Renderer/RendererCore/Platform/Vulkan/Shaders
		std::ifstream file1("D:/Graphite/Graphite/src/Graphite/Renderer/RendererCore/Platform/Vulkan/Shaders/vert.spv", std::ios::binary | std::ios::ate);

		if(!file1.is_open())
		{
			throw std::runtime_error("Failed to open the vertex shader!");
		}

		size_t fileSize1 = (size_t)file1.tellg();
		
		std::vector<char> vertBuffer(fileSize1);

		file1.seekg(0);
		file1.read(
			vertBuffer.data(),
			fileSize1);

		file1.close();
		
		std::ifstream file2("D:/Graphite/Graphite/src/Graphite/Renderer/RendererCore/Platform/Vulkan/Shaders/frag.spv", std::ios::ate | std::ios::binary);

		if (!file2.is_open())
		{
			throw std::runtime_error("Failed to open the fragment shader!");
		}
		
		size_t fileSize2 = (size_t)file2.tellg();
		std::vector<char> fragBuffer(fileSize2);

		file2.seekg(0);
		file2.read(
			fragBuffer.data(),
			fileSize2);

		file2.close();
		

		VkShaderModule vertModule;
		VkShaderModule fragModule;

		VkShaderModuleCreateInfo shaderCreateInfo = {};
		shaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderCreateInfo.codeSize = vertBuffer.size();
		shaderCreateInfo.pCode = reinterpret_cast<const uint32_t*>(vertBuffer.data());

		VkResult result = vkCreateShaderModule(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &shaderCreateInfo, nullptr, &vertModule);
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a vertex shader module!");
		}

		shaderCreateInfo.codeSize = fragBuffer.size();
		shaderCreateInfo.pCode = reinterpret_cast<const uint32_t*>(fragBuffer.data());

		result = vkCreateShaderModule(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), &shaderCreateInfo, nullptr, &fragModule);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a fragment shader module!");
		}
		
		VkPipelineShaderStageCreateInfo vertInfo = {};
		vertInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertInfo.module = vertModule;
		vertInfo.pName = "main";
		
		VkPipelineShaderStageCreateInfo fragInfo = {};
		fragInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragInfo.module = fragModule;
		fragInfo.pName = "main";
		
		VkPipelineShaderStageCreateInfo shaderInfos[] = { vertInfo, fragInfo };

		// .............................. ADD VERTEX BINDING DESCRIPTIONS AND VERTEX INPUT ....................................
		VkVertexInputBindingDescription vertexBindingDescription = {};
		vertexBindingDescription.binding = 0;			// Defaault binding for all the vertex data in the vert shader
		vertexBindingDescription.stride = sizeof(Vertex);
		vertexBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions;

		// Position Attribute
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, position);

		// Color Attribute
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);
		
		// Texture uv-s Attribute
		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, textureCoords);

		// Normal Attribute
		attributeDescriptions[3].binding = 0;
		attributeDescriptions[3].location = 3;
		attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[3].offset = offsetof(Vertex, normal);

		VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo = {};
		vertexInputCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputCreateInfo.vertexBindingDescriptionCount = 1;
		vertexInputCreateInfo.pVertexBindingDescriptions = &vertexBindingDescription;
		vertexInputCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputCreateInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
		
		
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
		inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

		VkDynamicState dynamicStates[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
		
		VkPipelineDynamicStateCreateInfo dynamicStateInfo = {};
		dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicStateInfo.dynamicStateCount = 2;
		dynamicStateInfo.pDynamicStates = dynamicStates;

		VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
		rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
		rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_TRUE;
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

		// Make an array of descriptor set layouts
		std::array<VkDescriptorSetLayout, 2> descriptorSetLayouts = {s_DescriptorSetLayout, s_SamplerDescriptorSetLayout};

		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
		pipelineLayoutCreateInfo.pSetLayouts = descriptorSetLayouts.data();
		pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
		pipelineLayoutCreateInfo.pPushConstantRanges = &s_PushConstantRange;
		
		result = vkCreatePipelineLayout(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&pipelineLayoutCreateInfo,
			nullptr,
			&s_GraphicsPipelineLayout);
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
		pipelineCreateInfo.pVertexInputState = &vertexInputCreateInfo;
		pipelineCreateInfo.pDynamicState = &dynamicStateInfo;
		pipelineCreateInfo.pViewportState = nullptr;
		pipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
		pipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
		pipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
		pipelineCreateInfo.pColorBlendState = &colorBlendCreateInfo;
		pipelineCreateInfo.pDepthStencilState = &depthStencilStateCreateInfo;
		pipelineCreateInfo.layout = s_GraphicsPipelineLayout;
		pipelineCreateInfo.renderPass = s_RenderPass;
		pipelineCreateInfo.subpass = 0;

		pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineCreateInfo.basePipelineIndex = -1;
		
		result = vkCreateGraphicsPipelines(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			VK_NULL_HANDLE,
			1,
			&pipelineCreateInfo,
			nullptr,
			&s_GraphicsPipeline);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a pipeline");
		}

		vkDestroyShaderModule(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), vertModule, nullptr);
		vkDestroyShaderModule(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), fragModule, nullptr);
	}

	void VulkanRendererAPI::CreateCommandPool()
	{
		VkCommandPoolCreateInfo commandPoolCreateInfo = {};
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.queueFamilyIndex = GR_GRAPHICS_CONTEXT->GetQueueFamiliesIndices().GraphicsFamily;
		commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		VkResult result = vkCreateCommandPool(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&commandPoolCreateInfo,
			nullptr,
			&s_GraphicsCommandPool);

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
		descriptorPoolCreateInfo.pPoolSizes = poolSizes.data();
		descriptorPoolCreateInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());

		VkResult result = vkCreateDescriptorPool(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&descriptorPoolCreateInfo,
			nullptr,
			&s_DescriptorPool);
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a descriptor set pool!");
		}

		VkDescriptorPoolSize samplerPoolSize = {};
		samplerPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerPoolSize.descriptorCount = static_cast<uint32_t>(s_FrameBuffer->Size());

		std::vector<VkDescriptorPoolSize> samplerPoolSizes = { samplerPoolSize };

		VkDescriptorPoolCreateInfo samplerDescriptorPoolCreateInfo = {};
		samplerDescriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		samplerDescriptorPoolCreateInfo.maxSets = MAX_OBJECTS;
		samplerDescriptorPoolCreateInfo.maxSets = 1;
		samplerDescriptorPoolCreateInfo.pPoolSizes = samplerPoolSizes.data();
		samplerDescriptorPoolCreateInfo.poolSizeCount = static_cast<uint32_t>(samplerPoolSizes.size());

		vkCreateDescriptorPool(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&samplerDescriptorPoolCreateInfo,
			nullptr,
			&s_SamplerDescriptorPool);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a descriptor set pool!");
		}
	}

	void VulkanRendererAPI::CreatePushConstantRange()
	{
		s_PushConstantRange = {};
		s_PushConstantRange.stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS;
		s_PushConstantRange.offset = 0;
		s_PushConstantRange.size = sizeof(VulkanUtilities::PushConstantsData);
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

	void VulkanRendererAPI::CreateDescriptorSetLayouts()
	{
		VkDescriptorSetLayoutBinding vpLayoutBinding = {};
		vpLayoutBinding.binding = 0;
		vpLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		vpLayoutBinding.descriptorCount = 1;
		vpLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		vpLayoutBinding.pImmutableSamplers = nullptr;

		std::vector<VkDescriptorSetLayoutBinding> layoutBindings = { vpLayoutBinding };

		VkDescriptorSetLayoutCreateInfo layoutCreateInfo = {};
		layoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutCreateInfo.bindingCount = static_cast<uint32_t>(layoutBindings.size());
		layoutCreateInfo.pBindings = layoutBindings.data();

		VkResult result = vkCreateDescriptorSetLayout(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&layoutCreateInfo,
			nullptr,
			&s_DescriptorSetLayout);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a Descriptor Set Layout!");
		}

		VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
		samplerLayoutBinding.binding = 0;
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.descriptorCount = 1;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		samplerLayoutBinding.pImmutableSamplers = nullptr;

		VkDescriptorSetLayoutCreateInfo textureLayoutCreateInfo = {};
		textureLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		textureLayoutCreateInfo.bindingCount = 1;
		textureLayoutCreateInfo.pBindings = &samplerLayoutBinding;

		result = vkCreateDescriptorSetLayout(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&textureLayoutCreateInfo,
			nullptr,
			&s_SamplerDescriptorSetLayout);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a Descriptor Set Layout!");
		}
	}

}

#endif
