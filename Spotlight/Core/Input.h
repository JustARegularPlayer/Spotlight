#pragma once

#include "splpch.h"

namespace Spotlight
{

	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return sm_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return sm_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePos() { return sm_Instance->GetMousePosImpl(); }
		inline static float GetMouseXPos() { return sm_Instance->GetMouseXPosImpl(); }
		inline static float GetMouseYPos() { return sm_Instance->GetMouseYPosImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXPosImpl() = 0;
		virtual float GetMouseYPosImpl() = 0;

	private:
		static Input* sm_Instance;
	};

}