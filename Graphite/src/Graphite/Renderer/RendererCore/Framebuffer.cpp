#include "Graphite/Core/grpch.h"
#include "FrameBuffer.h"
#include "./Platform/Vulkan/VulkanFrameBuffer.h"

namespace Graphite
{

	FrameBuffer* FrameBuffer::CreateFrameBuffer()
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		return new VulkanFrameBuffer();
#endif
	}

	
}
