#include "splpch.h"
#include "WinInput.h"

#include "Spotlight/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Spotlight
{

	Input* Input::sm_Instance = new WinInput();

	bool WinInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(SpotlightApp::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WinInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(SpotlightApp::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WinInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(SpotlightApp::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return {(float) xPos, (float) yPos};
	}

	float WinInput::GetMouseXPosImpl()
	{
		return GetMousePosImpl().first;
	}

	float WinInput::GetMouseYPosImpl()
	{
		return GetMousePosImpl().second;
	}
}