#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_TIMER_H
#define GRAPHITE_TIMER_H

namespace Graphite
{
	class GRAPHITE_API Timer
	{
	public:
		Timer();
		virtual ~Timer() = default;

		void Start();
		void Stop();
		std::chrono::microseconds Delta();
		
	private:
		std::chrono::microseconds m_StartingTime;
		std::chrono::microseconds m_FinalTime;
	};
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif