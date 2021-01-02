#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanValidator.h"

namespace Graphite
{
#ifndef GR_DIST
	bool VulkanValidator::s_Status = true;
#else
	bool VulkanValidatod::s_Status = false;
#endif

	const std::vector<const char*> VulkanValidator::s_ValidationLayers = { "VK_LAYER_LUNARG_standard_validation" };

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanValidator::DebugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* message,
		void* userData)
	{
		if(flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
		{
			GR_LOG_CRITICAL("VALIDATION ERROR: {0}", message);
		}
		else if(flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
		{
			GR_LOG_WARN("VALIDATION WARNING: {0}", message);
		}

		return VK_FALSE;
	}

	VkResult VulkanValidator::CreateDebugReportCallbackEXT(
		VkInstance instance,
		const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugReportCallbackEXT* pCallback)
	{
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");

		if(func != nullptr)
		{
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void VulkanValidator::DestroyDebugReportCallbackEXT(
		VkInstance instance,
		VkDebugReportCallbackEXT callback,
		const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");

		if (func != nullptr)
		{
			func(instance, callback, pAllocator);
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

		for (const auto& validationLayer : s_ValidationLayers)
		{
			bool hasLayer = false;
			for (const auto& availableLayer : availableLayers)
			{
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
