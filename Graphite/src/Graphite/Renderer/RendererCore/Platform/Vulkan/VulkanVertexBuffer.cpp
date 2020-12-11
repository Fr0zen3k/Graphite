#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanVertexBuffer.h"

namespace Graphite
{
	
	VulkanVertexBuffer::VulkanVertexBuffer(Vertex* pVertices, size_t size): m_BufferData(pVertices), m_Size(size) { }

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		FreeNativeBuffer();
	}

	void VulkanVertexBuffer::MapMemory()
	{
		
	}


	void VulkanVertexBuffer::AllocateNativeBuffer()
	{
		VkBufferCreateInfo bufferCreateInfo = {};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.size = sizeof(Vertex) * m_Size;
		bufferCreateInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VkResult result = vkCreateBuffer(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, &bufferCreateInfo, nullptr, &m_NativeBuffer);

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a vertex buffer!");
		}

		VkMemoryRequirements memReq = {};
		vkGetBufferMemoryRequirements(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, m_NativeBuffer, &memReq);

		VkMemoryAllocateInfo memAllocInfo = {};
		memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memAllocInfo.allocationSize = memReq.size;
		memAllocInfo.memoryTypeIndex = FindMemoryTypeIndex(memReq.memoryTypeBits,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		result = vkAllocateMemory(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, &memAllocInfo, nullptr, &m_BufferMemory);

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to allocate a vertex buffer to device memory!");
		}
	}

	void VulkanVertexBuffer::FreeNativeBuffer()
	{
		vkDestroyBuffer(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, m_NativeBuffer, nullptr);
		vkFreeMemory(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, m_BufferMemory, nullptr);
	}
	
}

#endif
