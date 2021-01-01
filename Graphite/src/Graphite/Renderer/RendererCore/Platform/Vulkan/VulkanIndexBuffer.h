#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VULKANINDEXBUFFER_H
#define GRAPHITE_VULKANINDEXBUFFER_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "vulkan/vulkan.h"

#include "../../IndexBuffer.h"

namespace Graphite
{

	class GRAPHITE_API VulkanIndexBuffer: public IndexBuffer
	{
	public:
		VulkanIndexBuffer(uint32_t* pIndices, size_t size);
		~VulkanIndexBuffer();

		inline size_t Size() const override { return m_Size; }

		inline VkBuffer GetNativeBuffer() const { return m_NativeBuffer; }
	private:
		void AllocateNativeBuffer(uint32_t* pIndices);
		void FreeNativeBuffer();

	private:
		size_t m_Size;

		VkBuffer m_NativeBuffer;
		VkDeviceMemory m_BufferMemory;
	};
	
}


#endif

#endif
