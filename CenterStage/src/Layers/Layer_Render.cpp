#include "Layer_Render.h"

#include <glm/gtc/matrix_transform.hpp>

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

	float squareVertices[3 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	uint32_t squareIndices[3 * 2] =
	{
		0, 1, 2,
		2, 3, 0
	};

	m_SquareVAO.reset(Spotlight::VertexArray::Create());

	std::shared_ptr<Spotlight::VertexBuffer> SquareVBO;
	SquareVBO.reset(Spotlight::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

	SquareVBO->SetLayout({
		{Spotlight::ShaderDataType::Float3, "i_Position"}
	});
	m_SquareVAO->AddVertexBuffer(SquareVBO);

	std::shared_ptr<Spotlight::IndexBuffer> SquareIBO;
	SquareIBO.reset(Spotlight::IndexBuffer::Create(squareIndices, (uint32_t)std::size(squareIndices)));
	m_SquareVAO->SetIndexBuffer(SquareIBO);

	m_SquareShader.reset(Spotlight::Shader::Create("assets/Shaders/Test.glsl"));
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
				Spotlight::Renderer::Submit(m_SquareShader, m_SquareVAO, transform);

			}
		}
		//Spotlight::Renderer::Submit(m_Shader, m_VAO);
	}
	Spotlight::Renderer::EndScene();
	
	// CONTROLS ========================================

	if(Spotlight::Input::IsKeyPressed(SPL_KEY_W))
		m_CameraPosition.y += m_CameraMoveSpeed * ts;
	if(Spotlight::Input::IsKeyPressed(SPL_KEY_S))
		m_CameraPosition.y -= m_CameraMoveSpeed * ts;
	
	if(Spotlight::Input::IsKeyPressed(SPL_KEY_A))
		m_CameraPosition.x -= m_CameraMoveSpeed * ts;
	if(Spotlight::Input::IsKeyPressed(SPL_KEY_D))
		m_CameraPosition.x += m_CameraMoveSpeed * ts;

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
		ImGui::ArrowButton("Back", ImGuiDir_Left);
	}
	ImGui::End();
}

void Layer_Render::OnEvent(Spotlight::Event &e)
{
}
