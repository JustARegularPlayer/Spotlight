#include <Spotlight.h>
#include <Spotlight/Core/EntryPoint.h>

#include "Layers/Sandbox2D.h"

class CenterStage : public Spotlight::SpotlightApp
{
public:
	CenterStage()
	{
		PushLayer(new Sandbox2D());
	}

	~CenterStage()
	{
	}
};

Spotlight::SpotlightApp* Spotlight::CreateApp()
{
	return new CenterStage();
}