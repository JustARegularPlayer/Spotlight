#include "Layer_Render.h"

Layer_Render::Layer_Render()
	: m_Camera({-1.6f, 1.6f, -0.9f, 0.9f}), m_CameraPosition(m_Camera.GetPosition()), m_CameraRotation(m_Camera.GetRotation())
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
		-0.75f, -0.75f, 0.0f,
		 0.75f, -0.75f, 0.0f,
		 0.75f,  0.75f, 0.0f,
		-0.75f,  0.75f, 0.0f,
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

void Layer_Render::OnUpdate()
{
	Spotlight::RenderCmd::SetClearColor({0.08f, 0.08f, 0.08f, 1.0f});
	Spotlight::RenderCmd::Clear();

	Spotlight::Renderer::BeginScene(m_Camera);
	{
		Spotlight::Renderer::Submit(m_SquareShader, m_SquareVAO);
		Spotlight::Renderer::Submit(m_Shader, m_VAO);
	}
	Spotlight::Renderer::EndScene();

	if(Spotlight::Input::IsKeyPressed(SPL_KEY_W))
		m_CameraPosition.y += 0.05f;
	if(Spotlight::Input::IsKeyPressed(SPL_KEY_A))
		m_CameraPosition.x -= 0.05f;
	if(Spotlight::Input::IsKeyPressed(SPL_KEY_S))
		m_CameraPosition.y -= 0.05f;
	if(Spotlight::Input::IsKeyPressed(SPL_KEY_D))
		m_CameraPosition.x += 0.05f;

	m_Camera.SetPosition(m_CameraPosition);

	if (Spotlight::Input::IsKeyPressed(SPL_KEY_Q))
		m_CameraRotation += 2.0f;
	if (Spotlight::Input::IsKeyPressed(SPL_KEY_E))
		m_CameraRotation -= 2.0f;

	m_Camera.SetRotation(m_CameraRotation);
}

void Layer_Render::OnUIRender()
{
	ImGui::Begin("Render");
	{
		ImGui::Text("This is a rectangle AND a triangle! Wicked, right?");
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
