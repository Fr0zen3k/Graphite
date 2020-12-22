#include "Graphite/Core/grpch.h"
#include "VertexBuffer.h"

#include "Platform/Vulkan/VulkanVertexBuffer.h"

namespace Graphite
{

	VertexBuffer* VertexBuffer::CreateVertexBuffer(Vertex* pVertices, size_t size)
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		return new VulkanVertexBuffer(pVertices, size);
#endif
	}

	
}
