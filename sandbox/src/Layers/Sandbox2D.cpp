#include "Sandbox2D.h"

#include <Platform/OpenGL/OpenGLShader.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: m_CameraController(16.0f / 9.0f, true)
{
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Spotlight::Timestep ts)
{
	// Updates from external components
	m_CameraController.OnUpdate(ts);

	// Rendering
	Spotlight::RenderCmd::SetClearColor({0.1f, 0.1f, 0.1f, 0.0f});
	Spotlight::RenderCmd::Clear();

	glm::vec2 scale = {0.2f, 0.2f};

	Spotlight::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		Spotlight::Renderer2D::DrawQuad({0.0f, 0.0f}, scale, m_Color);
	}
	Spotlight::Renderer2D::EndScene();
	
	// TODO: Add SetMat4(), SetFloat4() to base Shader class
	// std::dynamic_pointer_cast<Spotlight::OpenGLShader>(m_Shader)->Bind();
	//. std::dynamic_pointer_cast<Spotlight::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_Color);
}

void Sandbox2D::OnUIRender()
{
	ImGui::Begin("Properties");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
	ImGui::End();
}

void Sandbox2D::OnEvent(Spotlight::Event &e)
{
	m_CameraController.OnEvent(e);
}
