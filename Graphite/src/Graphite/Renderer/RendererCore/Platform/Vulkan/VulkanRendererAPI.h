#pragma once

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VULKANRENDERERAPI_H
#define GRAPHITE_VULKANRENDERERAPI_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"

#include "vulkan/vulkan.h"

#include "VulkanFrameBuffer.h"
#include "VulkanGraphicsContext.h"
#include "../../../Renderer2D/Renderer2D.h"
#include "../../GraphicsContext.h"
#include "VulkanShader.h"

namespace Graphite
{

	class GRAPHITE_API VulkanRendererAPI
	{
	public:
		static void Init();
		static void Shutdown();

		static bool OnEvent(const Event& e);

		static bool BindShader(VulkanShader* shader);

		inline static VkCommandPool GetGraphicsCommandPool() { return s_GraphicsCommandPool; }
		inline static VkSwapchainKHR GetSwapchain() { return s_Swapchain; }
		inline static VkRenderPass GetRenderPass() { return s_RenderPass; }
		inline static VkDescriptorPool GetDescriptorPool() { return s_DescriptorPool; }
		inline static VkDescriptorPool GetSamplerDescriptorPool() { return s_SamplerDescriptorPool; }

	private:
		static void CreateSwapchain();
		static void CreateRenderPass();
		static void CreateGraphicsPipeline();
		static void RecreateGraphicsPipeline();
		static void CreateCommandPool();
		static void CreateDescriptorPools();
		static void CreatePushConstantRange();
		static void CreateSynchronisation();
		
	private:
		static const int MAX_OBJECTS = 10000;
		static const int MAX_FRAME_DRAWS = 2;
		
		static VulkanFrameBuffer* s_FrameBuffer;

		static VkSwapchainKHR s_Swapchain;
		
		static VkRenderPass s_RenderPass;
		
		static VkPipeline s_GraphicsPipeline;
		static VkPipelineLayout s_GraphicsPipelineLayout;

		static VulkanShader* s_VertexShader;
		static VulkanShader* s_FragmentShader;

		static VkCommandPool s_GraphicsCommandPool;

		static VkDescriptorPool s_DescriptorPool;
		static VkDescriptorPool s_SamplerDescriptorPool;

		static VkPushConstantRange s_PushConstantRange;

		static std::vector<VkSemaphore> s_ImageAvailableSemaphores;
		static std::vector<VkSemaphore> s_RenderFinishSemaphores;
		static std::vector<VkFence> s_DrawFences;
	};
	
}

#endif

#endif
