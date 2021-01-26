#include "Graphite/Core/grpch.h"
#include "Camera.h"

#include "Platform/Vulkan/VulkanOrthographicCamera.h"
#include "Platform/Vulkan/VulkanPerspectiveCamera.h"

namespace Graphite
{

	Camera* Camera::CreateCamera(CameraType type)
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		if(type == CameraType::Orthographic)
		{
			return new VulkanOrthographicCamera();
		}

		if(type == CameraType::Perspective)
		{
			return new VulkanPerspectiveCamera();
		}
		
#endif
	}

	
}
