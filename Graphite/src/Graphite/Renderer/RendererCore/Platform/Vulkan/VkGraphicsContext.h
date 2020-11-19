#pragma once

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_RENDERCONTEX_H
#define GRAPHITE_RENDERCONTEX_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/Core/Application.h"
#include "Graphite/Core/Window.h"
#include "Graphite/EventCore/Events.h"

#include "Utils.h"

#include "GLFW/glfw3.h"

namespace Graphite
{
	class GRAPHITE_API VkGraphicsContext
	{
		friend class Renderer2D;
		friend class Renderer3D;
	public:
		VkGraphicsContext();
		~VkGraphicsContext();

		bool OnEvent(Event& e);

		inline void SetFrameSize(uint32_t width, uint32_t height)
		{
			m_FrameSize.first = width;
			m_FrameSize.second = height;
		}

		inline std::pair<uint32_t, uint32_t> GetFrameSize() { return m_FrameSize; }
		inline GLFWwindow* GetNativeWindow() { return m_ActiveApplication->GetWindow().GetNativeWindow(); }
		
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
		
		std::pair<uint32_t, uint32_t> m_FrameSize;
		QueueFamilies m_QueueFamilies;
	};
}

#endif
#endif
