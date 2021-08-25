#include <Spotlight.h>

#include <imgui.h>

class Layer_Test : public Spotlight::Layer
{
public:
	void OnUpdate() override
	{
	}

	void OnUIRender() override
	{
		ImGui::Begin("Test");
		{
			ImGui::Text("A triangle?!");
		}
		ImGui::End();
	}
	
	void OnEvent(Spotlight::Event& e) override
	{
	}

private:
	int m_Number1 = 0;
	int m_Number2 = 0;
};

class CenterStage : public Spotlight::SpotlightApp
{
public:
	CenterStage()
	{
		PushLayer(new Layer_Test());
	}

	~CenterStage()
	{
	}
};

Spotlight::SpotlightApp* Spotlight::CreateApp()
{
	return new CenterStage();
}