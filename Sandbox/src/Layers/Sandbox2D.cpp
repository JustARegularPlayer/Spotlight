#include "Sandbox2D.h"

#include <glm/gtc/type_ptr.hpp>

#define PROFILE_SCOPE(name) Spotlight::Timer timer##__LINE__(name, [&](ProfileResults profileResult) { m_ProfileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D()
	: m_Controller(16.0f / 9.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	Spotlight::Renderer2D::Init();

	m_Texture = Spotlight::Texture2D::Create("assets/Textures/default.png");
}

void Sandbox2D::OnDetach()
{
	Spotlight::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(Spotlight::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2D::OnUpdate");
	// Updating external components
	{
		m_Controller.OnUpdate(ts);
	}
	// Rendering
	Spotlight::RenderCmd::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Spotlight::RenderCmd::Clear();

	Spotlight::Renderer2D::BeginScene(m_Controller.GetCamera());
	Spotlight::Renderer2D::DrawQuad({0.0f, 0.0f, 0.0f}, 0.0f, {20.0f, 20.0f}, m_Texture, m_Tiles);
	Spotlight::Renderer2D::DrawQuad({2.0f, 1.3f, 0.1f}, 0.0f, {1.0f, 1.0f}, m_Color1);
	Spotlight::Renderer2D::DrawQuad({-1.5f, -0.3f, 0.2f}, 0.0f, {1.0f, 1.0f}, m_Color2);
	Spotlight::Renderer2D::EndScene();
}

void Sandbox2D::OnUIRender()
{
	ImGui::Begin("Quad");
	{
		ImGui::SliderFloat("Texture Tiles", &m_Tiles, 1.0f, 20.0f, "%f Tiles", 1.0f);
		ImGui::ColorEdit4("Quad Color 1", glm::value_ptr(m_Color1));
		ImGui::ColorEdit4("Quad Color 2", glm::value_ptr(m_Color2));
		ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
	}
	ImGui::End();
	ImGui::Begin("Profiler");
	{
		for (auto result : m_ProfileResults)
		{
			char label[50];
			strcpy(label, "%.3fms - ");
			strcat(label, result.Name);
			ImGui::Text(label, result.Time);
		}
		m_ProfileResults.clear();
	}
	ImGui::End();
}

void Sandbox2D::OnEvent(Spotlight::Event &e)
{
	m_Controller.OnEvent(e);
}
