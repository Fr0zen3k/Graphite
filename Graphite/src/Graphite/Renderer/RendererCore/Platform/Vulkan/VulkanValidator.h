#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VULKANVALIDATOR_H
#define GRAPHITE_VULKANVALIDATOR_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "vulkan/vulkan.h"

namespace Graphite
{
	class GRAPHITE_API VulkanValidator
	{
	public:
		inline static const char* GetExtensionName() { return VK_EXT_DEBUG_REPORT_EXTENSION_NAME; }

		inline static bool Status() { return s_Status; }
		
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t obj,
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* message,
			void* userData);

		static VkResult CreateDebugReportCallbackEXT(
			VkInstance instance,
			const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, 
			const VkAllocationCallbacks* pAllocator,
			VkDebugReportCallbackEXT* pCallback);

		static void DestroyDebugReportCallbackEXT(
			VkInstance instance,
			VkDebugReportCallbackEXT callback,
			const VkAllocationCallbacks* pAllocator);

		static bool CheckValidationSupport();

		inline static const char* const* GetValidationLayers() { return s_ValidationLayers.data(); }
		inline static size_t GetValidationLayerSize() { return s_ValidationLayers.size(); }
		
	private:
		static bool s_Status;
		static const std::vector<const char*> s_ValidationLayers;
	};
}


#endif

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif