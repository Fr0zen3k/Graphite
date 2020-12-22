#pragma once

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VKFRAMEBUFFER_H
#define GRAPHITE_VKFRAMEBUFFER_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"

#include "VulkanShader.h"

#include "vulkan/vulkan.h"

namespace Graphite
{
	class GRAPHITE_API VulkanFrameBuffer
	{
	public:
		VulkanFrameBuffer();
		~VulkanFrameBuffer();

		bool OnEvent(Event& e);

		void DrawFrame();

	private:
		void Init();
		void Shutdown();

		void CreateSwapchain();
		void CreateFrames();


		void CreateCommandPool();
		
	private:		
		VkSwapchainKHR m_Swapchain;

		// Add appropriate descriptor set layouts and push constants for the needed functionality

		// Add corresponding descriptor pools for the used layouts

		// Add uniform buffer if needed		

		class RenderPass
		{
		public:
			RenderPass();
			~RenderPass();

			bool OnEvent(Event& e);

			inline VkRenderPass GetNativeRenderPass() { return m_RenderPass; }

		private:
			void Init();
			void Shutdown();

			void CreateRenderPass();
			void CreateCommandPool();

		private:
			VkRenderPass m_RenderPass;

			VkCommandPool m_CommandPool;
		};

		// Later add support for usage of compute pipelines as well
		// Add connection with the render pass used for the pipeline
		class Pipeline
		{
		public:
			Pipeline();
			~Pipeline();

			bool OnEvent(Event& e);

			bool BindShader(VulkanShader& shader);

		private:
			void Init();
			void Shutdown();

			void CreatePipeline();
			void RecreatePipeline();

		private:
			VkPipeline m_Pipeline;
			VkPipelineLayout m_PipelineLayout;

			VulkanShader m_VertexShader;
			VulkanShader m_FragmentShader;
			// Add support for more different shaders including compute shaders

			RenderPass m_RenderPass;
		};

		class GRAPHITE_API Frame
		{
			friend class Renderer2D;
			friend class Renderer3D;
			friend class VulkanFrameBuffer;
		public:
			Frame(VkImage image);
			~Frame();

			bool OnEvent(Event& e);

			inline void SetImage(VkImage& image)
			{
				m_Image = image;
			}

			inline void AssignCommandPool(VkCommandPool& commandPool)
			{
				CreateCommandBuffer(commandPool);
			}

			inline void BindRenderPass(RenderPass* renderPass)
			{
				m_RenderPass = renderPass;
				CreateFramebuffer();
			}

			
			inline Frame operator =  (Frame f)
			{
				Frame res(f.m_Image);
				return res;
			}

			inline VkCommandBuffer GetCommandBuffer()
			{
				return m_CommandBuffer;
			}

			void CreateFramebuffer();

			void CreateCommandBuffer(VkCommandPool& commandPool);

			void CreateColorImage();

			void CreateDepthBufferImage();

		private:
			void Init();
			void Shutdown();

			void CreateImageView();

		private:
			VkImage m_Image;
			VkImageView m_ImageView;
			
			VkFramebuffer m_Framebuffer;
			
			VkCommandBuffer m_CommandBuffer;

			VkImage m_ColorBufferImage;
			VkDeviceMemory m_ColorBufferImageMemory;
			VkImageView m_ColorImageView;

			VkImage m_DepthBufferImage;
			VkDeviceMemory m_DepthBufferImageMemory;
			VkImageView m_DepthBufferImageView;

			RenderPass* m_RenderPass;
		};
		
		std::vector<Frame*> m_Frames;
		size_t m_BufferSize = 0;

		Pipeline* m_MainPipeline;
		RenderPass* m_MainRenderPass;

		VulkanShader* m_VertexShader;
		VulkanShader* m_FragmentShader;

		VkCommandPool m_CommandPool;
	};
}

#endif

#endif
