#include "Layer_Render.h"

Layer_Render::Layer_Render()
{
	float vertices[7 * 3] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};

	uint32_t indices[3 * 2] = {0, 1, 2};

	m_VAO.reset(Spotlight::VertexArray::Create());

	std::shared_ptr<Spotlight::VertexBuffer> VBO;
	VBO.reset(Spotlight::VertexBuffer::Create(vertices, sizeof(vertices)));

	Spotlight::BufferLayout layout =
	{
		{Spotlight::ShaderDataType::Float3, "i_Position", false},
		{Spotlight::ShaderDataType::Float4, "i_Color", false},
	};

	VBO->SetLayout(layout);
	m_VAO->AddVertexBuffer(VBO);

	std::shared_ptr<Spotlight::IndexBuffer> IBO;
	IBO.reset(Spotlight::IndexBuffer::Create(indices, (uint32_t)std::size(indices)));
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

	Spotlight::Renderer::BeginScene();
	{
		m_SquareShader->Bind();
		Spotlight::Renderer::Submit(m_SquareVAO);

		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.3f, 0.2f, 0.8f, 1.0f);
		Spotlight::Renderer::Submit(m_VAO);
	}
	Spotlight::Renderer::EndScene();
}

void Layer_Render::OnUIRender()
{
	ImGui::Begin("Render");
	{
		ImGui::Text("This is a rectangle AND a triangle!");
		ImGui::Text("Wicked, right?");
		ImGui::ArrowButton("Back", ImGuiDir_Left);
	}
	ImGui::End();
}

void Layer_Render::OnEvent(Spotlight::Event &e)
{
}
