#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanIndexBuffer.h"

#include "Utils.h"
#include "VulkanGraphicsContext.h"
#include "../../../Renderer3D/Renderer3D.h"
#include "VulkanRendererAPI.h"

namespace Graphite
{
	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* pIndices, size_t size): m_Size(size), IndexBuffer()
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

		VulkanUtilities::CreateBuffer(
			GR_GRAPHICS_CONTEXT->GetPhysicalDevice(),
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			bufferSize,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			&m_NativeBuffer,
			&m_BufferMemory);

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		VulkanUtilities::CreateBuffer(
			GR_GRAPHICS_CONTEXT->GetPhysicalDevice(),
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&stagingBuffer,
			&stagingBufferMemory);

		void* data;
		vkMapMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingBufferMemory,
			0,
			bufferSize,
			0,
			&data);
		memcpy(
			data,
			pIndices,
			m_Size * sizeof(uint32_t));
		vkUnmapMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingBufferMemory);

		VulkanUtilities::CopyBuffer(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			GR_GRAPHICS_CONTEXT->GetGraphicsQueue(),
			VulkanRendererAPI::GetGraphicsCommandPool(),
			stagingBuffer,
			m_NativeBuffer,
			bufferSize);

		vkDestroyBuffer(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingBuffer,
			nullptr);
		vkFreeMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingBufferMemory,
			nullptr);
	}

	void VulkanIndexBuffer::FreeNativeBuffer()
	{
		vkDestroyBuffer(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_NativeBuffer,
			nullptr);
		vkFreeMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_BufferMemory,
			nullptr);
	}
}

#endif
