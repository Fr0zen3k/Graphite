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
		inline static const char* GetExtensionName() { return VK_EXT_DEBUG_UTILS_EXTENSION_NAME; }

		inline static bool Status() { return s_Status; }
		
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageSeverityFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

		static VkResult CreateDebugUtilsMessengerEXT(
			VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pMessenger);

		static void DestroyDebugUtilsMessengerEXT(
			VkInstance instance,
			VkDebugUtilsMessengerEXT debugMessenger,
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