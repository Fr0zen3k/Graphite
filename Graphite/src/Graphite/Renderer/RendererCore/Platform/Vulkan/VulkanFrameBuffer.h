#ifndef GRAPHITE_VKFRAMEBUFFER_H
#define GRAPHITE_VKFRAMEBUFFER_H

#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifdef GRAPHITE_RENDERER_VULKAN

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"
#include "../../FrameBuffer.h"

#include "vulkan/vulkan.h"

namespace Graphite
{
	struct GRAPHITE_API Frame
	{
		VkImage Image;
		VkImageView ImageView;

		VkFramebuffer Framebuffer;

		VkCommandBuffer CommandBuffer;

		VkBuffer UniformBufferVP;
		VkDeviceMemory UniformBufferMemVP;

		VkDescriptorSet DescriptorSet;
	};
	
	class GRAPHITE_API VulkanFrameBuffer : public FrameBuffer
	{	
	public:
		VulkanFrameBuffer();
		~VulkanFrameBuffer() override;

		bool OnEvent(Event& e) override;

		void UpdateViewProjectionUniform(uint32_t currentFrame);

		inline size_t Size() const override { return m_BufferSize; }

		inline Frame& operator [] (int i) { return m_Frames[i]; }

		inline Frame& GetFrame(uint32_t index) { return m_Frames[index]; }

	private:
		void Init();
		void Shutdown();

		void CreateFrames();
		void InitDepthTesting();
		void UpdateDepthTesting();
		void ShutdownDepthTesting();
		void CreateFramebuffers();
		void CreateCommandBuffers();
		void CreateUniformBuffers();
		void CreateDescriptorSets();
		void CreateImageViews();
		
	private:
		std::vector<Frame> m_Frames;
		size_t m_BufferSize = 0;

		VkImage m_DepthBufferImage;
		VkDeviceMemory m_DepthBufferDeviceMemory;
		VkImageView m_DepthBufferImageView;
	};
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif

#endif
