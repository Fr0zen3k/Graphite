#include "Graphite/Core/grpch.h"
#include "IndexBuffer.h"

#include "Platform/Vulkan/VulkanIndexBuffer.h"

namespace Graphite
{
	IndexBuffer* IndexBuffer::CreateIndexBuffer(uint32_t* pIndices, size_t size)
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		return new VulkanIndexBuffer(pIndices, size);
#endif
	}
	
}
