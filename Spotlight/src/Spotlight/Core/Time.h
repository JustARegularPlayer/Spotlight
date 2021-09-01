#pragma once

namespace Spotlight
{

	class Time
	{
	public:
		virtual ~Time() {}

		virtual void UpdateTime() = 0;
		virtual float GetTime() = 0;

		static Time *Create();
	};

}