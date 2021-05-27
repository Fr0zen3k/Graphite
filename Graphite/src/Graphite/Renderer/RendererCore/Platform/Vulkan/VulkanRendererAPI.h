#ifndef GRAPHITE_VULKANRENDERERAPI_H
#define GRAPHITE_VULKANRENDERERAPI_H

#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifdef GRAPHITE_RENDERER_VULKAN

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"

#include "vulkan/vulkan.h"

#include "VulkanFrameBuffer.h"
#include "VulkanShader.h"
#include "VulkanTexture.h"
#include "VulkanIndexBuffer.h"
#include "VulkanVertexBuffer.h"

#include "Graphite/Assets/Material.h"

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
		inline static VkDescriptorSetLayout GetDescriptorSetLayout() { return s_DescriptorSetLayout; }
		inline static VkDescriptorSetLayout GetSamplerDescriptorSetLayout() { return s_SamplerDescriptorSetLayout; }
		inline static VkSurfaceFormatKHR GetSwapchainSurfaceFormat() { return s_SwapchainSurfaceFormat; }

		static uint32_t StartDrawing();
		static void Draw(uint32_t imageIndex, VulkanVertexBuffer * pVertexBuffer, VulkanIndexBuffer * pIndexBuffer, VulkanTexture * pTexture, const glm::mat4& modelMatrix, const Material& material);
		static void EndDrawing(uint32_t imageIndex);

	private:
		static void CreateSwapchain();
		static void CreateRenderPass();
		static void CreateGraphicsPipeline();
		static void CreateCommandPool();
		static void CreateDescriptorPools();
		static void CreatePushConstantRange();
		static void CreateSynchronisation();
		static void CreateDescriptorSetLayouts();
		
	private:
		static const int MAX_OBJECTS = 65536;
		static const int MAX_FRAME_DRAWS = 2;
		
		static VulkanFrameBuffer* s_FrameBuffer;

		static VkSwapchainKHR s_Swapchain;
		static VkSurfaceFormatKHR s_SwapchainSurfaceFormat;
		
		static VkRenderPass s_RenderPass;
		
		static VkPipeline s_GraphicsPipeline;
		static VkPipelineLayout s_GraphicsPipelineLayout;

		static VulkanShader* s_VertexShader;
		static VulkanShader* s_FragmentShader;

		static VkCommandPool s_GraphicsCommandPool;

		static VkDescriptorPool s_DescriptorPool;
		static VkDescriptorPool s_SamplerDescriptorPool;

		static VkDescriptorSetLayout s_DescriptorSetLayout;
		static VkDescriptorSetLayout s_SamplerDescriptorSetLayout;

		static VkPushConstantRange s_PushConstantRange;

		static std::vector<VkSemaphore> s_ImageAvailableSemaphores;
		static std::vector<VkSemaphore> s_RenderFinishSemaphores;
		static std::vector<VkFence> s_DrawFences;

		static uint8_t s_CurrentFrame;
	};
	
}

#endif

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif