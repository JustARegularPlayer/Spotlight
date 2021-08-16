#pragma once

#include "Spotlight/Core/Input.h"

namespace Spotlight
{

class WinInput : public Input 
{
protected:
	bool IsKeyPressedImpl(int keycode) override;
	bool IsMouseButtonPressedImpl(int button) override;
	std::pair<float, float> GetMousePosImpl() override;
	float GetMouseXPosImpl() override;
	float GetMouseYPosImpl() override;
};

}

