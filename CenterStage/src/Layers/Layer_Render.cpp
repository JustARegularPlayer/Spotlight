#include "Layer_Render.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Temporary includes
#include "Platform/OpenGL/OpenGLShader.h"

Layer_Render::Layer_Render()
	: m_Camera({-1.6f, 1.6f, -0.9f, 0.9f}), 
	m_CameraPosition(m_Camera.GetPosition()), 
	m_CameraRotation(m_Camera.GetRotation())
{
	float vertices[7 * 3] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};

	uint32_t indices[3 * 2] = {0, 1, 2};

	m_VAO.reset(Spotlight::VertexArray::Create());

	std::shared_ptr<Spotlight::VertexBuffer> VBO;
	VBO.reset(Spotlight::VertexBuffer::Create(vertices, sizeof(vertices)));

	VBO->SetLayout({
		{Spotlight::ShaderDataType::Float3, "i_Position", false},
		{Spotlight::ShaderDataType::Float4, "i_Color", false},
	});
	m_VAO->AddVertexBuffer(VBO);

	std::shared_ptr<Spotlight::IndexBuffer> IBO;
	IBO.reset(Spotlight::IndexBuffer::Create(indices, (uint32_t) std::size(indices)));
	m_VAO->SetIndexBuffer(IBO);

	m_Shader.reset(Spotlight::Shader::Create("assets/Shaders/Basic.glsl"));

	float solidColorVertices[3 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	uint32_t solidColorIndices[3 * 2] =
	{
		0, 1, 2,
		2, 3, 0
	};

	m_SolidColorVAO.reset(Spotlight::VertexArray::Create());

	std::shared_ptr<Spotlight::VertexBuffer> SolidColorVBO;
	SolidColorVBO.reset(Spotlight::VertexBuffer::Create(solidColorVertices, sizeof(solidColorVertices)));

	SolidColorVBO->SetLayout({
		{Spotlight::ShaderDataType::Float3, "i_Position"}
	});
	m_SolidColorVAO->AddVertexBuffer(SolidColorVBO);

	std::shared_ptr<Spotlight::IndexBuffer> SolidColorIBO;
	SolidColorIBO.reset(Spotlight::IndexBuffer::Create(solidColorIndices, (uint32_t)std::size(solidColorIndices)));
	m_SolidColorVAO->SetIndexBuffer(SolidColorIBO);

	m_SolidColorShader.reset(Spotlight::Shader::Create("assets/Shaders/SolidColor.glsl"));
	m_SolidColor = {0.8f, 0.2f, 0.3f, 1.0f};
}

void Layer_Render::OnUpdate(Spotlight::Timestep ts)
{
	Spotlight::RenderCmd::SetClearColor({0.08f, 0.08f, 0.08f, 1.0f});
	Spotlight::RenderCmd::Clear();

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	
	Spotlight::Renderer::BeginScene(m_Camera);
	{
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				std::dynamic_pointer_cast<Spotlight::OpenGLShader>(m_SolidColorShader)->UploadUniformFloat4("u_Color", m_SolidColor);
				Spotlight::Renderer::Submit(m_SolidColorShader, m_SolidColorVAO, transform);

			}
		}
		//Spotlight::Renderer::Submit(m_Shader, m_VAO);
	}
	Spotlight::Renderer::EndScene();
	
	// CONTROLS ========================================

	float speed = m_CameraMoveSpeed;
	if (Spotlight::Input::IsKeyPressed(SPL_KEY_LEFT_SHIFT))
		speed *= 2;

	if(Spotlight::Input::IsKeyPressed(SPL_KEY_W))
		m_CameraPosition.y += speed * ts;
	if(Spotlight::Input::IsKeyPressed(SPL_KEY_S))
		m_CameraPosition.y -= speed * ts;
	
	if(Spotlight::Input::IsKeyPressed(SPL_KEY_A))
		m_CameraPosition.x -= speed * ts;
	if(Spotlight::Input::IsKeyPressed(SPL_KEY_D))
		m_CameraPosition.x += speed * ts;

	m_Camera.SetPosition(m_CameraPosition);

	if (Spotlight::Input::IsKeyPressed(SPL_KEY_Q))
		m_CameraRotation -= m_CameraRotateSpeed * ts;
	if (Spotlight::Input::IsKeyPressed(SPL_KEY_E))
		m_CameraRotation += m_CameraRotateSpeed * ts;

	m_Camera.SetRotation(m_CameraRotation);
}

void Layer_Render::OnUIRender()
{
	ImGui::Begin("Render");
	{
		ImGui::Text("ONE HUNDRED SQUARES?! Damn, son!");
		ImGui::Text("Position: (%.2f, %.2f)", m_Camera.GetPosition().x, m_Camera.GetPosition().y);
		ImGui::Text("Rotation: %.2f", m_Camera.GetRotation());
		ImGui::Text("%.2ffps", ImGui::GetIO().Framerate);
		ImGui::ColorEdit3("Solid Color", glm::value_ptr(m_SolidColor));
	}
	ImGui::End();
}

void Layer_Render::OnEvent(Spotlight::Event &e)
{
}
