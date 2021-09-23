#include "Sandbox2D.h"

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: m_Controller(16.0f / 9.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	Spotlight::Renderer2D::Init();
}

void Sandbox2D::OnDetach()
{
	Spotlight::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(Spotlight::Timestep ts)
{
	// Updating of external components
	m_Controller.OnUpdate(ts);

	// Rendering
	Spotlight::RenderCmd::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Spotlight::RenderCmd::Clear();

	Spotlight::Renderer2D::BeginScene(m_Controller.GetCamera());
	Spotlight::Renderer2D::DrawQuad({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, m_Color);
	Spotlight::Renderer2D::EndScene();
}

void Sandbox2D::OnUIRender()
{
	ImGui::Begin("Quad");
	{
		ImGui::ColorEdit4("Quad Color", glm::value_ptr(m_Color));
	}
	ImGui::End();
}

void Sandbox2D::OnEvent(Spotlight::Event &e)
{
	m_Controller.OnEvent(e);
}
