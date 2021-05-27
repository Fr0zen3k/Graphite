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

namespace Graphite
{

	class GRAPHITE_API Renderer2D
	{
	public:
		static void Init();
		static void InitAPI();
		static void OnTick();
		static void Shutdown();
		
		static GraphicsContext* GetGraphicsContext();
		
	private:
		static GraphicsContext* s_GraphicsContext;
	};

}


#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif