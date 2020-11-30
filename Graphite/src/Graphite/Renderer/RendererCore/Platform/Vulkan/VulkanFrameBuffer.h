#pragma once

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VKFRAMEBUFFER_H
#define GRAPHITE_VKFRAMEBUFFER_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"
#include "Graphite/Core/Application.h"
#include "Graphite/Core/Window.h"

#include "Utils.h"

#include "VulkanGraphicsContext.h"

#include "GLFW/glfw3.h"

namespace Graphite
{
	class GRAPHITE_API VulkanFrameBuffer
	{
	public:
		VulkanFrameBuffer();
		~VulkanFrameBuffer();

		bool OnEvent(Event& e);

	private:
		void Init();
		void Shutdown();

		void CreateSwapchain();
		void CreateFrames();
		
	private:
		static VulkanGraphicsContext* m_GraphicsContext;
		
		VkSwapchainKHR m_Swapchain;

		// Add appropriate descriptor set layouts and push constants for the needed functionality

		// Add corresponding descriptor pools for the used layouts

		// Add uniform buffer if needed		
		
		class GRAPHITE_API Frame
		{
			friend class Renderer2D;
			friend class Renderer3D;
			friend class VulkanFrameBuffer;
		public:
			Frame(VkImage image);
			~Frame();

			bool OnEvent(Event& e);

			inline Frame operator = (const Frame& f)
			{
				Frame res(f.m_Image);
				return res;
			}
			
		private:
			void Init();
			void Shutdown();

			void CreateImage();
			void CreateImageView();
			
			void CreateColorImage();
			
			void CreateDepthBufferImage();

			void CreateSynchronisation();

		private:
			VkImage m_Image;
			VkImageView m_ImageView;
			VkFramebuffer m_Framebuffer;
			VkCommandBuffer m_CommandBuffer;

			VkImage m_ColorBufferImage;
			VkDeviceMemory m_ColorBufferImageMemory;
			VkImageView m_ColorImageViews;

			VkImage m_DepthBufferImage;
			VkDeviceMemory m_DepthBufferImageMemory;
			VkImageView m_DepthBufferImageView;

			VkSemaphore m_ImageAvailabilitySemaphore;
			VkSemaphore m_ImageRenderFinish;
			VkFence m_DrawFence;
		};

		class Pipeline
		{
		public:
			Pipeline();
			~Pipeline();

			bool OnEvent(Event& e);

		private:
			void Init();
			void Shutdown();

			void CreatePipeline();

		private:
			VkPipeline m_Pipeline;
			VkPipelineLayout m_PipelineLayout;
			
		};

		class RenderPass
		{
		public:
			RenderPass();
			~RenderPass();

			bool OnEvent(Event& e);

			bool BindPipeline(const Pipeline& pipeline);
			
		private:
			void Init();
			void Shutdown();
			
		private:
			VkRenderPass m_RenderPass;

			VkCommandPool m_CommandPool;

			std::vector<Pipeline> m_Pipelines;
		};

		std::vector<Frame> m_Frames;
		size_t m_BufferSize = 0;

		Pipeline m_MainPipeline;
		RenderPass m_MainRenderPass;
	};
}

#endif

#endif
