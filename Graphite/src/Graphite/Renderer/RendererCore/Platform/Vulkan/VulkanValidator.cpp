#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanValidator.h"

namespace Graphite
{
#ifndef GR_DIST
	bool VulkanValidator::s_Status = true;
#else
	bool VulkanValidator::s_Status = false;
#endif

	const std::vector<const char*> VulkanValidator::s_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanValidator::DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageSeverityFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		if(messageSeverity > VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			GR_LOG_CRITICAL("VALIDATION ERROR: {0}", pCallbackData->pMessage);
		}

		return VK_FALSE;
	}

	VkResult VulkanValidator::CreateDebugUtilsMessengerEXT(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pMessenger);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void VulkanValidator::DestroyDebugUtilsMessengerEXT(
		VkInstance instance,
		VkDebugUtilsMessengerEXT debugMessenger,
		const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}

	bool VulkanValidator::CheckValidationSupport()
	{
		uint32_t validationLayerCount;
		vkEnumerateInstanceLayerProperties(
			&validationLayerCount,
			nullptr);

		if (validationLayerCount == 0 && s_ValidationLayers.size() > 0)
		{
			return false;
		}

		std::vector<VkLayerProperties> availableLayers(validationLayerCount);
		vkEnumerateInstanceLayerProperties(
			&validationLayerCount,
			availableLayers.data());

		for(auto a : availableLayers)
		{
			std::cout << a.layerName << std::endl;
		}

		for (const auto& validationLayer : s_ValidationLayers)
		{
			bool hasLayer = false;
			for (const auto& availableLayer : availableLayers)
			{
				std::cout << validationLayer << ", " << availableLayer.layerName << std::endl;
				if (strcmp(validationLayer, availableLayer.layerName) == 0)
				{
					hasLayer = true;
					break;
				}
			}

			if (!hasLayer)
			{
				return false;
			}
		}

		return true;
	}

}


#endif
