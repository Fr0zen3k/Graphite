#pragma once

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VKFRAMEBUFFER_H
#define GRAPHITE_VKFRAMEBUFFER_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"
#include "Graphite/Core/Application.h"
#include "Graphite/Core/Window.h"

#include "VulkanGraphicsContext.h"

#include "GLFW/glfw3.h"

namespace Graphite
{
	class GRAPHITE_API Frame
	{
		friend class Renderer2D;
		friend class Renderer3D;
	public:
		Frame() = default;
		~Frame() = default;
		
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
	
	class GRAPHITE_API VulkanFrameBuffer
	{
	public:

		
	private:
		
	};
}

#endif

#endif
