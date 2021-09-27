#pragma once

#include <chrono>
#include "Spotlight/Core/Core.h"

namespace Spotlight
{

	class Time
	{
	public:
		virtual ~Time() {}

		virtual void UpdateTime() = 0;
		virtual float GetTime() = 0;

		static Scope<Time> Create();
	};

	template<typename Fn>
	class Timer
	{
	public:
		Timer(const char *name, Fn &&func)
			: m_Name(name), m_Func(func), m_IsStopped(false)
		{
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			if (!m_IsStopped)
				Stop();
		}

		void Stop()
		{
			auto endTimePoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

			float duration = (end - start) * 0.001f;
			m_Func({m_Name, duration});
			m_IsStopped = true;
		}
	private:
		const char *m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
		Fn m_Func;
		bool m_IsStopped = false;
	};

}