#include "Graphite/Core/grpch.h"
#include "Timer.h"

namespace Graphite
{
	Timer::Timer()
	{
		Start();
	}

	void Timer::Start()
	{
		auto now = std::chrono::system_clock::now();
		auto nowMs = std::chrono::time_point_cast<std::chrono::microseconds>(now);
		auto epoch = nowMs.time_since_epoch();
		auto val = std::chrono::duration_cast<std::chrono::microseconds>(epoch);
		m_StartingTime = std::chrono::microseconds(val);
	}

	void Timer::Stop()
	{
		auto now = std::chrono::system_clock::now();
		auto nowMs = std::chrono::time_point_cast<std::chrono::microseconds>(now);
		auto epoch = nowMs.time_since_epoch();
		auto val = std::chrono::duration_cast<std::chrono::microseconds>(epoch);
		m_FinalTime = std::chrono::microseconds(val);
	}

	std::chrono::microseconds Timer::Delta()
	{
		return m_FinalTime - m_StartingTime;
	}

}
