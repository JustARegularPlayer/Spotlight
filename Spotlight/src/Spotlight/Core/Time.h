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

}