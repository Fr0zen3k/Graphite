#pragma once

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VULKANVERTEXBUFFER_H
#define GRAPHITE_VULKANVERTEXBUFFER_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"
#include "Utils.h"

#include "VulkanFrameBuffer.h"
#include "VulkanGraphicsContext.h"

#include "vulkan/vulkan.h"

namespace Graphite
{

	class GRAPHITE_API VulkanVertexBuffer
	{
	public:
		VulkanVertexBuffer(Vertex* pVertices, size_t size);
		~VulkanVertexBuffer();

		inline Vertex* GetBufferData() { return m_BufferData; }
		inline size_t Size() { return m_Size; }

		inline void SetData(Vertex* pVertices, size_t size) { m_BufferData = pVertices; m_Size = size; }

		inline VkBuffer GetNativeBuffer() { return m_NativeBuffer; }

		void MapMemory();

	private:
		void AllocateNativeBuffer();
		void FreeNativeBuffer();
		
	private:
		Vertex* m_BufferData;
		size_t m_Size;

		VkBuffer m_NativeBuffer;
		VkDeviceMemory m_BufferMemory;
	};
	
}

#endif

#endif

