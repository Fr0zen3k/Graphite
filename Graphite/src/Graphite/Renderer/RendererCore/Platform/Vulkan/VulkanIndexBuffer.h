#pragma once

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VULKANINDEXBUFFER_H
#define GRAPHITE_VULKANINDEXBUFFER_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "vulkan/vulkan.h"

#include "Utils.h"
#include "VulkanGraphicsContext.h"
#include "../../../Renderer2D/Renderer2D.h"

namespace Graphite
{

	class VulkanIndexBuffer
	{
	public:
		VulkanIndexBuffer(uint32_t* pIndices, size_t size);
		~VulkanIndexBuffer();

		inline size_t Size() const { return m_Size; }

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
