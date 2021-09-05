#include "splpch.h"
#include "WinTime.h"

#include <GLFW/glfw3.h>

namespace Spotlight
{

	Scope<Time> Time::Create()
	{
		return std::make_unique<WinTime>();
	}

	WinTime::WinTime()
	{
	}

	WinTime::~WinTime()
	{
	}

	void WinTime::UpdateTime()
	{
		m_Time = (float) glfwGetTime();
	}

}