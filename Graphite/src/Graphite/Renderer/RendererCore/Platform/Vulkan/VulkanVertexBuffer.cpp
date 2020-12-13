#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanVertexBuffer.h"

#include "Utils.h"
#include "VulkanFrameBuffer.h"
#include "VulkanGraphicsContext.h"
#include "../../../Renderer2D/Renderer2D.h"

namespace Graphite
{
	
	VulkanVertexBuffer::VulkanVertexBuffer(Vertex* pVertices, size_t size):m_Size(size), VertexBuffer()
	{
		AllocateNativeBuffer(pVertices);
	}

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		FreeNativeBuffer();
	}


	void VulkanVertexBuffer::AllocateNativeBuffer(Vertex* pVertices)
	{
		VkDeviceSize bufferSize = sizeof(Vertex) * m_Size;
		
		CreateBuffer(GR_GRAPHICS_CONTEXT->GetPhysicalDevice(), GR_GRAPHICS_CONTEXT->GetLogicalDevice(), bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT
			| VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &m_NativeBuffer, &m_BufferMemory);

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		CreateBuffer(GR_GRAPHICS_CONTEXT->GetPhysicalDevice(), GR_GRAPHICS_CONTEXT->GetLogicalDevice(), bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingBuffer, &stagingBufferMemory);

		void* data;
		vkMapMemory(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, pVertices, m_Size * sizeof(Vertex));
		vkUnmapMemory(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), stagingBufferMemory);

		CopyBuffer(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), transferQueue, transferCommandPool, stagingBuffer, m_NativeBuffer, bufferSize);

		vkDestroyBuffer(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), stagingBuffer, nullptr);
		vkFreeMemory(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), stagingBufferMemory, nullptr);
	}

	void VulkanVertexBuffer::FreeNativeBuffer()
	{
		vkDestroyBuffer(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), m_NativeBuffer, nullptr);
		vkFreeMemory(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), m_BufferMemory, nullptr);
	}
	
}

#endif
