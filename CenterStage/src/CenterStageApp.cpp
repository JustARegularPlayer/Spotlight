#include "Spotlight.h"

class Layer_Test : public Spotlight::Layer
{
public:
	void OnUpdate() override
	{
		SPL_INFO("Layer_Test Updated");
	}

	void OnEvent(Spotlight::Event& e) override
	{
	}
};

class CenterStage : public Spotlight::SpotlightApp
{
public:
	CenterStage()
	{
		PushLayer(new Layer_Test());
		PushOverlay(new Spotlight::Layer_ImGui());
	}

	~CenterStage()
	{
	}
};

Spotlight::SpotlightApp* Spotlight::CreateApp()
{
	return new CenterStage();
}