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

		inline size_t Size() const { return m_Size; }

		inline VkBuffer GetNativeBuffer() const { return m_NativeBuffer; }

	private:
		void AllocateNativeBuffer(Vertex* pVertices);
		void FreeNativeBuffer();
		
	private:
		size_t m_Size;

		VkBuffer m_NativeBuffer;
		VkDeviceMemory m_BufferMemory;
	};
	
}

#endif

#endif

