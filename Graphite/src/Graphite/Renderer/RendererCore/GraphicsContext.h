#ifndef GRAPHITE_GRAPHICSCONTEXT_H
#define GRAPHITE_GRAPHICSCONTEXT_H

#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"

#include "GLFW/glfw3.h"

namespace Graphite
{

	class GRAPHITE_API GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;
		
		virtual bool OnEvent(Event& e) = 0;
		
		virtual void SetFrameSize(uint32_t width, uint32_t height) = 0;

		virtual std::pair<uint32_t, uint32_t> GetFrameSize() const = 0;
		
		virtual GLFWwindow* GetNativeWindow() const = 0;

		static GraphicsContext* GetContext();
	};
	
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif
