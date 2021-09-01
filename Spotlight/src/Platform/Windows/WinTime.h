#pragma once

#include "Spotlight/Core/Time.h"

namespace Spotlight
{

	class WinTime : public Time
	{
	public:
		WinTime();
		~WinTime();

		virtual void UpdateTime() override;
		virtual float GetTime() override { return m_Time; }
	private:
		float m_Time = 0.0f;
	};

}