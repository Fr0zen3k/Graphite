#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_FRAMEBUFFER_H
#define GRAPHITE_FRAMEBUFFER_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"

namespace Graphite
{

	class GRAPHITE_API FrameBuffer
	{
	public:
		FrameBuffer() = default;
		virtual ~FrameBuffer() = default;

		virtual bool OnEvent(Event& e) = 0;

		virtual size_t Size() const = 0;

		static FrameBuffer* CreateFrameBuffer();
	};
	
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif