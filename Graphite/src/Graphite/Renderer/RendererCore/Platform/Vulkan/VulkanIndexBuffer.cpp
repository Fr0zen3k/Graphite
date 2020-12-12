#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanIndexBuffer.h"

namespace Graphite
{
	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* pIndices, size_t size): m_Size(size)
	{
		AllocateNativeBuffer(pIndices);
	}

	VulkanIndexBuffer::~VulkanIndexBuffer()
	{
		FreeNativeBuffer();
	}

	void VulkanIndexBuffer::AllocateNativeBuffer(uint32_t* pIndices)
	{
		VkDeviceSize bufferSize = sizeof(Vertex) * m_Size;

		CreateBuffer(VulkanFrameBuffer::GetGraphicsContext()->m_PhysicalDevice, VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT
			| VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &m_NativeBuffer, &m_BufferMemory);

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		CreateBuffer(VulkanFrameBuffer::GetGraphicsContext()->m_PhysicalDevice, VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingBuffer, &stagingBufferMemory);

		void* data;
		vkMapMemory(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, pIndices, m_Size * sizeof(Vertex));
		vkUnmapMemory(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, stagingBufferMemory);

		CopyBuffer(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, transferQueue, transferCommandPool, stagingBuffer, m_NativeBuffer, bufferSize);

		vkDestroyBuffer(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, stagingBuffer, nullptr);
		vkFreeMemory(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, stagingBufferMemory, nullptr);
	}

	void VulkanIndexBuffer::FreeNativeBuffer()
	{
		vkDestroyBuffer(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, m_NativeBuffer, nullptr);
		vkFreeMemory(VulkanFrameBuffer::GetGraphicsContext()->m_LogicalDevice, m_BufferMemory, nullptr);
	}
}

#endif
