#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanGraphicsContext.h"
#include "VulkanValidator.h"

namespace Graphite
{

	VulkanGraphicsContext::VulkanGraphicsContext()
	{
		try
		{
			Init();
		}
		catch (std::runtime_error& e)
		{
			throw e;
		}
	}

	VulkanGraphicsContext::~VulkanGraphicsContext()
	{
		Shutdown();
	}


	bool VulkanGraphicsContext::OnEvent(Event& e)
	{
		EventDispatch dispatcher(e);

		dispatcher.Dispatch<WindowResizeEvent>([&](WindowResizeEvent e)
		{
				m_FrameSize.first = static_cast<uint32_t>(e.GetHeight());
				m_FrameSize.second = static_cast<uint32_t>(e.GetWidth());
				return true; 
		});

		return true;
	}


	void VulkanGraphicsContext::Init()
	{
		m_ActiveApplication = Application::Get();
		
		SetFrameSize(m_ActiveApplication->GetWindow()->GetWidth(), m_ActiveApplication->GetWindow()->GetHeight());

		m_DeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		try
		{
			CreateInstance();
			CreateDebugMessenger();
			ChoosePhysicalDevice();
			CreateSurface();
			GetQueueFamilies();
			CreateLogicalDevice();
		}
		catch (std::runtime_error& e)
		{
			throw e;
		}
	}

	void VulkanGraphicsContext::Shutdown()
	{
		vkDeviceWaitIdle(m_LogicalDevice);

		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
		vkDestroyDevice(m_LogicalDevice, nullptr);
		vkDestroyInstance(m_Instance, nullptr);
	}

	
	void VulkanGraphicsContext::CreateInstance()
	{
		m_ApplicationInfo = {};
		m_ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		m_ApplicationInfo.pApplicationName = m_ActiveApplication->GetWindow()->m_Data.Title.c_str();
		m_ApplicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		m_ApplicationInfo.pEngineName = "Graphite Engine";
		m_ApplicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
		m_ApplicationInfo.apiVersion = VK_API_VERSION_1_2;

		VkInstanceCreateInfo instanceInfo = {};
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pApplicationInfo = &m_ApplicationInfo;
		
		uint32_t glfwExtensionCount;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions;

		for(uint32_t i = 0; i < glfwExtensionCount; i++)
		{
			extensions.push_back(glfwExtensions[i]);
		}

		if(VulkanValidator::Status())
		{
			extensions.push_back(VulkanValidator::GetExtensionName());
		}

		if(!VulkanUtilities::CheckInstanceExtensions(extensions))
		{
			throw std::runtime_error("Renderer extensions not supported!");
		}

		instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		instanceInfo.ppEnabledExtensionNames = extensions.data();
		
		if(VulkanValidator::Status())
		{
			instanceInfo.enabledLayerCount = static_cast<uint32_t>(VulkanValidator::GetValidationLayerSize());
			instanceInfo.ppEnabledLayerNames = VulkanValidator::GetValidationLayers();
		}
		else
		{
			instanceInfo.enabledLayerCount = 0;
			instanceInfo.ppEnabledLayerNames = nullptr;
		}
		
		VkResult result = vkCreateInstance(
			&instanceInfo,
			nullptr,
			&m_Instance);
		
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a Vulkan instance!");
		}
	}

	void VulkanGraphicsContext::ChoosePhysicalDevice()
	{
		m_PhysicalDevice = VK_NULL_HANDLE;

		uint32_t devCount = 0;
		vkEnumeratePhysicalDevices(
			m_Instance,
			&devCount,
			nullptr);

		if(devCount == 0)
		{
			throw std::runtime_error("No Vukan supported physical devices found!");
		}

		std::vector<VkPhysicalDevice> devices(devCount);
		vkEnumeratePhysicalDevices(
			m_Instance,
			&devCount,
			devices.data());

		std::multimap<int, VkPhysicalDevice> candidates;

		for (const auto& device : devices) {
			int score = VulkanUtilities::RatePhysicalDevice(device);
			candidates.insert(std::make_pair(score, device));
		}
		
		if (candidates.rbegin()->first > 0) {
			m_PhysicalDevice = candidates.rbegin()->second;
		}
		else {
			throw std::runtime_error("failed to find a suitable GPU!");
		}

		vkGetPhysicalDeviceProperties(
			m_PhysicalDevice,
			&m_PhysicalDeviceProperties);
		vkGetPhysicalDeviceFeatures(
			m_PhysicalDevice,
			&m_PhysicalDeviceFeatures);
		vkGetPhysicalDeviceMemoryProperties(
			m_PhysicalDevice, 
			&m_PhysicalDeviceMemoryProperties);

		if(m_PhysicalDeviceProperties.limits.maxPushConstantsSize < 256)
		{
			throw std::runtime_error("Insufficient device push constants size.");
		}
	}

	void VulkanGraphicsContext::CreateLogicalDevice()
	{
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<int> queueFamilyIndices = { m_QueueFamilies.GraphicsFamily, m_QueueFamilies.PresentationFamily };

		for(int index : queueFamilyIndices)
		{
			VkDeviceQueueCreateInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			info.queueFamilyIndex = index;
			info.queueCount = 1;
			float priority = 1.0f;
			info.pQueuePriorities = &priority;

			queueCreateInfos.push_back(info);
		}

		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(m_DeviceExtensions.size());
		deviceCreateInfo.ppEnabledExtensionNames = m_DeviceExtensions.data();

		VkPhysicalDeviceFeatures features = {};
		features.samplerAnisotropy = VK_TRUE;

		deviceCreateInfo.pEnabledFeatures = &features;

		VkResult result = vkCreateDevice(
			m_PhysicalDevice,
			&deviceCreateInfo,
			nullptr,
			&m_LogicalDevice);
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a logical device!");
		}

		vkGetDeviceQueue(
			m_LogicalDevice,
			m_QueueFamilies.GraphicsFamily,
			0,
			&m_GraphicsQueue);
		vkGetDeviceQueue(
			m_LogicalDevice,
			m_QueueFamilies.PresentationFamily,
			0,
			&m_PresentationQueue);
	}

	void VulkanGraphicsContext::CreateSurface()
	{
		VkResult result = glfwCreateWindowSurface(
			m_Instance,
			GetNativeWindow(),
			nullptr,
			&m_Surface);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a surface!");
		}
	}
	

	void VulkanGraphicsContext::GetQueueFamilies()
	{
		uint32_t familyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(
			m_PhysicalDevice,
			&familyCount,
			nullptr);

		std::vector<VkQueueFamilyProperties> properties(familyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(
			m_PhysicalDevice,
			&familyCount,
			properties.data());

		for(int i = 0; i <= properties.size(); i++)
		{
			if(properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				m_QueueFamilies.GraphicsFamily = i;
			}

			VkBool32 presentationSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(
				m_PhysicalDevice,
				i,
				m_Surface,
				&presentationSupport);
			
			if(properties[i].queueCount > 0 && presentationSupport)
			{
				m_QueueFamilies.PresentationFamily = i;
			}

			if(m_QueueFamilies.areFamiliesValid())
			{
				break;
			}
		}
	}

	void VulkanGraphicsContext::CreateDebugMessenger()
	{
		if (!VulkanValidator::Status()) { return; }

		VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = VulkanValidator::DebugCallback;
		createInfo.pUserData = nullptr;

		VkResult result = VulkanValidator::CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugMessenger);
		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a debug messenger");
		}
	}

	void VulkanGraphicsContext::SetBenchmarkingValues() const
	{
		Application::Get()->GetBenchmarker()->SetGPUBrand(m_PhysicalDeviceProperties.deviceName);
		Application::Get()->GetBenchmarker()->SetMaxTextureSize(m_PhysicalDeviceProperties.limits.maxImageDimension2D);
		Application::Get()->GetBenchmarker()->SetMaxPushConstantSize(m_PhysicalDeviceProperties.limits.maxPushConstantsSize);
		Application::Get()->GetBenchmarker()->SetVRAM(m_PhysicalDeviceMemoryProperties.memoryHeaps[0].size / 1024);
	}

}

#endif
