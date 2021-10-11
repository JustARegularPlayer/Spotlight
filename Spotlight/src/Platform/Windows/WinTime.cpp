#include "splpch.h"
#include "WinTime.h"

#include <GLFW/glfw3.h>

namespace Spotlight
{

	Scope<Time> Time::Create()
	{
		return CreateScope<WinTime>();
	}

	WinTime::WinTime()
	{
	}

	WinTime::~WinTime()
	{
	}

	float WinTime::GetTime()
	{
		return glfwGetTime();
	}

}