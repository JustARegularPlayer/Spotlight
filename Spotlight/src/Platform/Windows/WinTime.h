#pragma once

#include "Spotlight/Core/Time.h"

namespace Spotlight
{

	class WinTime : public Time
	{
	public:
		WinTime();
		~WinTime();

		virtual float GetTime() override;
	};

}