#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_GRAPHICSCONTEXT_H
#define GRAPHITE_GRAPHICSCONTEXT_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"

#include "GLFW/glfw3.h"

namespace Graphite
{

	class GRAPHITE_API GraphicsContext
	{
	public:
		virtual bool OnEvent(Event& e) = 0;
		
		virtual void SetFrameSize(uint32_t width, uint32_t height) = 0;

		virtual std::pair<uint32_t, uint32_t> GetFrameSize() const = 0;
		
		virtual GLFWwindow* GetNativeWindow() const = 0;

		static GraphicsContext* GetContext();
	};
	
}

#endif
