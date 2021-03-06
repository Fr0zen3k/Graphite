#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

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
#include "vulkan/vulkan.hpp"

#include "../../GraphicsContext.h"

namespace Graphite
{
	class GRAPHITE_API VulkanGraphicsContext : public GraphicsContext
	{
	public:
		VulkanGraphicsContext();
		~VulkanGraphicsContext() override;

		bool OnEvent(Event& e) override;

		inline void SetFrameSize(uint32_t width, uint32_t height) override
		{
			m_FrameSize.first = width;
			m_FrameSize.second = height;
		}

		inline std::pair<uint32_t, uint32_t> GetFrameSize() const override { return m_FrameSize; }
		inline GLFWwindow* GetNativeWindow() const override { return m_ActiveApplication->GetWindow()->GetNativeWindow(); }

		// Getters
		inline VkInstance GetInstance() const { return m_Instance; }
		
		inline VkPhysicalDevice GetPhysicalDevice() const { return m_PhysicalDevice; }
		inline VkDevice GetLogicalDevice() const { return m_LogicalDevice; }
		
		inline VkQueue GetGraphicsQueue() const { return m_GraphicsQueue; }
		inline VkQueue GetPresentationQueue() const { return m_PresentationQueue; }

		inline VkSurfaceKHR GetSurface() const { return m_Surface; }
		inline VkFormat GetSwapchainImageFormat() const { return m_SwapchainImageFormat; }
		inline VkExtent2D GetSwapchainExtent() const { return m_SwapchainExtent; }
		inline VkColorSpaceKHR GetSwapchainColorSpace() const { return m_SwapchainColorSpace; }

		inline VulkanUtilities::QueueFamilies GetQueueFamiliesIndices() { return m_QueueFamilies; }

		// Setters
		inline void SetSwapchainExtent(VkExtent2D extent) { m_SwapchainExtent = extent; }
		inline void SetSwapchainImageFormat(VkFormat format) { m_SwapchainImageFormat = format; }
		inline void SetSwapchainColorSpace(VkColorSpaceKHR colorSpace) { m_SwapchainColorSpace = colorSpace; }

		inline void SetBenchmarkingValues() const;
		
	private:
		void Init();
		void Shutdown();
		void CreateInstance();
		void ChoosePhysicalDevice();
		void CreateLogicalDevice();
		void CreateSurface();
		void CreateDebugMessenger();
		
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
		VkPhysicalDeviceMemoryProperties m_PhysicalDeviceMemoryProperties;
		VkDevice m_LogicalDevice;
		VkQueue m_GraphicsQueue;
		VkQueue m_PresentationQueue;
		std::vector<const char*> m_DeviceExtensions;

		// Swapchain related components
		VkSurfaceKHR m_Surface;
		VkFormat m_SwapchainImageFormat;
		VkExtent2D m_SwapchainExtent;
		VkColorSpaceKHR m_SwapchainColorSpace;

		VkDebugUtilsMessengerEXT m_DebugMessenger;
		
		std::pair<uint32_t, uint32_t> m_FrameSize;
		VulkanUtilities::QueueFamilies m_QueueFamilies;
	};
}

#endif

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif