#pragma once

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VULKANGRAPHICSCONTEXT_H
#define GRAPHITE_VULKANGRAPHICSCONTEXT_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/Core/Application.h"
#include "Graphite/Core/Window.h"
#include "Graphite/EventCore/Events.h"

#include "Utils.h"

#include "GLFW/glfw3.h"

#include "Graphite/Renderer/RendererCore/GraphicsContext.h"

namespace Graphite
{
	class GRAPHITE_API VulkanGraphicsContext : public GraphicsContext
	{
		friend class Renderer2D;
		friend class Renderer3D;
		friend class VulkanFrameBuffer;
		friend class VulkanShader;
	public:
		VulkanGraphicsContext();
		~VulkanGraphicsContext();

		bool OnEvent(Event& e) override;

		inline void SetFrameSize(uint32_t width, uint32_t height) override
		{
			m_FrameSize.first = width;
			m_FrameSize.second = height;
		}

		inline std::pair<uint32_t, uint32_t> GetFrameSize() const override { return m_FrameSize; }
		inline GLFWwindow* GetNativeWindow() const override { return m_ActiveApplication->GetWindow().GetNativeWindow(); }
		
	private:
		void Init();
		void Shutdown();
		void CreateInstance();
		void ChoosePhysicalDevice();
		void CreateLogicalDevice();
		void CreateSurface();
		
		void GetQueueFamilies();

	private:
		// Pointer to the active (least recently created) Graphite application instance
		Application* m_ActiveApplication;

		// Application, devices and their properties
		VkApplicationInfo m_ApplicationInfo;
		VkInstance m_Instance;
		VkPhysicalDevice m_PhysicalDevice;
		VkPhysicalDeviceProperties m_PhysicalDeviceProperties;
		VkPhysicalDeviceFeatures m_PhysicalDeviceFeatures;
		VkDevice m_LogicalDevice;
		VkQueue m_GraphicsQueue;
		VkQueue m_PresentationQueue;
		std::vector<const char*> m_DeviceExtensions;

		// Swapchain related components
		VkSurfaceKHR m_Surface;
		VkFormat m_SwapchainImageFormat;
		VkExtent2D m_SwapchainExtent;
		VkColorSpaceKHR m_SwapchainColorSpace;
		
		std::pair<uint32_t, uint32_t> m_FrameSize;
		QueueFamilies m_QueueFamilies;
	};
}

#endif
#endif
