#include "splpch.h"
#include "WinTime.h"

#include <GLFW/glfw3.h>

namespace Spotlight
{

	Time *Time::Create()
	{
		return new WinTime();
	}

	WinTime::WinTime()
	{
	}

	WinTime::~WinTime()
	{
	}

	void WinTime::UpdateTime()
	{
		m_Time = glfwGetTime();
	}

}