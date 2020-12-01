#pragma once

#ifndef GRAPHITE_UTILS_H
#define GRAPHITE_UTILS_H

#include "GLFW/glfw3.h"
#include "Graphite/Core/grpch.h"

namespace Graphite
{

	enum class ShaderType
	{
		None,
		Vertex,
		Tessellation,
		Geometry,
		Fragment
		// Add support for compute shaders as well
	};


	struct QueueFamilies
	{
		int m_GraphicsFamily = -1;
		int m_PresentationFamily = -1;

		inline bool areFamiliesValid()
		{
			if(m_GraphicsFamily >= 0 && m_PresentationFamily >= 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};

	struct SwapchainInfo
	{
		VkSurfaceCapabilitiesKHR m_SurfaceCapabilities;
		std::vector<VkSurfaceFormatKHR>  m_SurfaceFormats;
		std::vector<VkPresentModeKHR> m_PresentModes;

		// Further extend and allow definition of color class based on the formats
		inline VkSurfaceFormatKHR ChooseBestSurfaceFormat()
		{
			if (m_SurfaceFormats.size() == 1 && m_SurfaceFormats[0].format == VK_FORMAT_UNDEFINED)
			{
				return { VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
			}

			for (const auto& format : m_SurfaceFormats)
			{
				if ((format.format == VK_FORMAT_R8G8B8A8_UNORM || format.format == VK_FORMAT_B8G8R8A8_UNORM)
					&& format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				{
					return format;
				}
			}

			return m_SurfaceFormats[0];
		}

		inline VkPresentModeKHR ChooseBestPresentMode()
		{
			for (const auto& presentationMode : m_PresentModes)
			{
				if (presentationMode == VK_PRESENT_MODE_MAILBOX_KHR)
				{
					return presentationMode;
				}
			}

			return VK_PRESENT_MODE_FIFO_KHR;
		}

		inline VkExtent2D ChooseSwapchainExtent(GLFWwindow * window)
		{
			if (m_SurfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
			{
				return m_SurfaceCapabilities.currentExtent;
			}
			else
			{
				int width, height;
				glfwGetFramebufferSize(window, &width, &height);

				VkExtent2D newExtent = {};
				newExtent.width = static_cast<uint32_t>(width);
				newExtent.height = static_cast<uint32_t>(height);

				newExtent.width = std::max(m_SurfaceCapabilities.minImageExtent.width, std::min(m_SurfaceCapabilities.maxImageExtent.width, newExtent.width));
				newExtent.height = std::max(m_SurfaceCapabilities.minImageExtent.height, std::min(m_SurfaceCapabilities.maxImageExtent.height, newExtent.height));

				return newExtent;
			}
		}
	};

	static SwapchainInfo GetSwapchainDetails(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		SwapchainInfo info;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &info.m_SurfaceCapabilities);

		uint32_t count = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &count, nullptr);

		if(count > 0)
		{
			info.m_PresentModes.resize(count);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &count, info.m_PresentModes.data());
		}

		count = 0;

		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &count, nullptr);

		if(count > 0)
		{
			info.m_SurfaceFormats.resize(count);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &count, info.m_SurfaceFormats.data());
		}

		return info;
	}

	static bool CheckInstanceExtensions(std::vector<const char*>& extensions)
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> supportedExtensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, supportedExtensions.data());

		for (const auto& checkExtension : extensions)
		{
			bool supported = false;

			for (const auto& extension : supportedExtensions)
			{
				if (strcmp(checkExtension, extension.extensionName) == 0)
				{
					supported = false;
					break;
				}
			}

			if (!supported)
			{
				return false;
			}
		}

		return true;
	}

	static int RatePhysicalDevice(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;

		vkGetPhysicalDeviceProperties(device, &properties);
		vkGetPhysicalDeviceFeatures(device, &features);

		int score = 0;

		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			score += 1000;
		}

		score += properties.limits.maxImageDimension2D;

		if (!features.geometryShader)
		{
			return 0;
		}

		return score;
	}
	
}

#endif
