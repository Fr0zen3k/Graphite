#include "Graphite/Core/grpch.h"
#include "GraphicsContext.h"

#include "Platform/Vulkan/VulkanGraphicsContext.h"

namespace Graphite
{

	GraphicsContext* GraphicsContext::GetContext()
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		return new VulkanGraphicsContext();
#endif
	}

	
}
