#ifndef GRAPHITE_VKFRAMEBUFFER_H
#define GRAPHITE_VKFRAMEBUFFER_H

#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifdef GRAPHITE_RENDERER_VULKAN

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"

#include "vulkan/vulkan.h"

namespace Graphite
{
	class GRAPHITE_API VulkanFrameBuffer
	{
		class GRAPHITE_API Frame
		{
		public:
			Frame(VkImage image);
			~Frame();

			bool OnEvent(Event& e);

			inline void SetImage(VkImage& image)
			{
				m_Image = image;
			}

			inline Frame operator =  (Frame f) const
			{
				Frame res(f.m_Image);
				return res;
			}

			inline VkCommandBuffer GetCommandBuffer() const
			{
				return m_CommandBuffer;
			}

			inline VkDescriptorSet GetDescriptorSet() const { return m_DescriptorSet; }

			inline VkFramebuffer GetNativeFramebuffer() const { return m_Framebuffer; }

			inline VkCommandBuffer* GetCommandBufferPointer() { return &m_CommandBuffer; }

			void UpdateViewProjectionUniform();

			static void InitDepthTesting();
			static void ShutdownDepthTesting();
			static void UpdateDepthTesting();

		private:
			void Init();
			void Shutdown();

			void CreateImageView();
			void CreateFramebuffer();
			void CreateCommandBuffer();
			void CreateUniformBuffer();
			void CreateDescriptorSet();

		private:
			VkImage m_Image;
			VkImageView m_ImageView;

			VkFramebuffer m_Framebuffer;

			VkCommandBuffer m_CommandBuffer;

			VkBuffer m_UniformBufferVP;
			VkDeviceMemory m_UniformBufferMemVP;

			VkDescriptorSet m_DescriptorSet;

			static VkImage s_DepthBufferImage;
			static VkDeviceMemory s_DepthBufferDeviceMemory;
			static VkImageView s_DepthBufferImageView;
		};
		
	public:
		VulkanFrameBuffer();
		~VulkanFrameBuffer();

		bool OnEvent(Event& e);

		inline void UpdateViewProjectionUniform(uint32_t currentFrame) { m_Frames[currentFrame]->UpdateViewProjectionUniform(); }

		inline size_t Size() const { return m_BufferSize; }

		inline Frame* operator [] (int i) { return m_Frames[i]; }

		inline Frame* GetFrame(uint32_t index) { return m_Frames[index]; }
	private:
		void Init();
		void Shutdown();

		void CreateFrames();
				
	private:
		std::vector<Frame*> m_Frames;
		size_t m_BufferSize = 0;
	};
}

#endif

#endif
