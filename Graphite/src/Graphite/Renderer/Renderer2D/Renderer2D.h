#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_RENDERER2D_H
#define GRAPHITE_RENDERER2D_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "../RendererCore/GraphicsContext.h"

#include "../RendererCore/Platform/Vulkan/VulkanGraphicsContext.h"
#include "../RendererCore/Platform/Vulkan/VulkanFrameBuffer.h"

namespace Graphite
{

	class GRAPHITE_API Renderer2D
	{
	public:
		static GraphicsContext* GetGraphicsContext();
		
	private:
		static GraphicsContext* s_GraphicsContext;
	};

}


#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif