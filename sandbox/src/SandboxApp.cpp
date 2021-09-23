#include <Spotlight.h>
#include <Spotlight/Core/EntryPoint.h>

#include "Layers/Sandbox2D.h"
#include "Layers/Layer_Render.h"

class Sandbox : public Spotlight::SpotlightApp
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
		// The PopLayer() is already done for you since clients cannot access
		// the layer stack, which is currently privately stored in SpotlightApp.

	}
};

Spotlight::SpotlightApp* Spotlight::CreateApp()
{
	return new Sandbox();
}