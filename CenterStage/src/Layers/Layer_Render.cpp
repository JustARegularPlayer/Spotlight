#include "Layer_Render.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Temporary includes
#include "Platform/OpenGL/OpenGLShader.h"

Layer_Render::Layer_Render()
	: m_CameraController(1366.0f / 768.0f, true)
{
	float solidColorVertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	uint32_t solidColorIndices[3 * 2] =
	{
		0, 1, 2,
		2, 3, 0
	};

	m_SolidColorVAO = Spotlight::VertexArray::Create();

	std::shared_ptr<Spotlight::VertexBuffer> SolidColorVBO;
	SolidColorVBO = Spotlight::VertexBuffer::Create(solidColorVertices, sizeof(solidColorVertices));

	SolidColorVBO->SetLayout({
		{Spotlight::ShaderDataType::Float3, "i_Position"},
		{Spotlight::ShaderDataType::Float2, "i_TexCoord"}
	});
	m_SolidColorVAO->AddVertexBuffer(SolidColorVBO);

	std::shared_ptr<Spotlight::IndexBuffer> SolidColorIBO;
	SolidColorIBO = Spotlight::IndexBuffer::Create(solidColorIndices, (uint32_t)std::size(solidColorIndices));
	m_SolidColorVAO->SetIndexBuffer(SolidColorIBO);

	m_SolidColorShader = Spotlight::Shader::Create("assets/Shaders/SolidColor.glsl");

	m_Library.Load("assets/Shaders/Texture.glsl");
	m_Texture = (Spotlight::Texture2D::Create("assets/Textures/pacman.png"));

	auto textureShader = m_Library.Get("Texture");

	// I suggest not to upload the texture to the shader inside a loop, quite unnecessary and *very* slow.
	std::dynamic_pointer_cast<Spotlight::OpenGLShader>(textureShader)->Bind();
	std::dynamic_pointer_cast<Spotlight::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	m_SolidColor = {0.8f, 0.2f, 0.3f, 1.0f};
}

void Layer_Render::OnUpdate(Spotlight::Timestep ts)
{
	// Updates from external components
	m_CameraController.OnUpdate(ts);

	// Rendering
	Spotlight::RenderCmd::SetClearColor({0.08f, 0.08f, 0.08f, 1.0f});
	Spotlight::RenderCmd::Clear();

	Spotlight::Renderer::BeginScene(m_CameraController.GetCamera());
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				std::dynamic_pointer_cast<Spotlight::OpenGLShader>(m_SolidColorShader)->Bind();
				std::dynamic_pointer_cast<Spotlight::OpenGLShader>(m_SolidColorShader)->UploadUniformFloat4("u_Color", m_SolidColor);
				Spotlight::Renderer::Submit(m_SolidColorShader, m_SolidColorVAO, transform);

			}
		}
		auto textureShader = m_Library.Get("Texture");
		m_Texture->Bind();
		Spotlight::Renderer::Submit(textureShader, m_SolidColorVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
	}
	Spotlight::Renderer::EndScene();
	
}

void Layer_Render::OnUIRender()
{
	ImGui::Begin("Solid Color");
		ImGui::ColorEdit3("Solid Color", &m_SolidColor.r);
	ImGui::End();

	ImGui::Begin("Render");
	{
		ImGui::Text("Look, it's PACMAN! HELL YEAH!");
		ImGui::Text("Position: (%.2f, %.2f)", m_CameraController.GetCamera().GetPosition().x, m_CameraController.GetCamera().GetPosition().y);
		ImGui::Text("Rotation: %.2f", m_CameraController.GetCamera().GetRotation());
		ImGui::Text("%.2ffps", ImGui::GetIO().Framerate);
	}
	ImGui::End();
}

void Layer_Render::OnEvent(Spotlight::Event &e)
{
	m_CameraController.OnEvent(e);
}
