#include "Sandbox2D.h"

#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: m_Controller(16.0f / 9.0f, true) {}

void Sandbox2D::OnAttach()
{
	SPL_PROFILE_FUNC();

	Spotlight::Renderer2D::Init();

	m_Texture = Spotlight::Texture2D::Create("assets/Textures/default.png");
}

void Sandbox2D::OnDetach()
{
	SPL_PROFILE_FUNC();

	Spotlight::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(Spotlight::Timestep ts)
{
	SPL_PROFILE_FUNC();

	// Updating external components
	m_Controller.OnUpdate(ts);

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
	SPL_PROFILE_FUNC();

	ImGui::Begin("Quad");
	{
		ImGui::SliderFloat("Texture Tiles", &m_Tiles, 1.0f, 20.0f, "%f Tiles", 1.0f);
		ImGui::ColorEdit4("Quad Color 1", glm::value_ptr(m_Color1));
		ImGui::ColorEdit4("Quad Color 2", glm::value_ptr(m_Color2));
		ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
	}
	ImGui::End();
}

void Sandbox2D::OnEvent(Spotlight::Event &e)
{
	SPL_PROFILE_FUNC();

	m_Controller.OnEvent(e);
}
