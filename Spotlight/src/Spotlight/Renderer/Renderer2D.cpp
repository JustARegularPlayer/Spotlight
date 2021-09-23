#include "splpch.h"
#include "Renderer2D.h"

#include "Spotlight/Renderer/VertexArray.h"
#include "Spotlight/Renderer/Shader.h"

#include "Spotlight/Renderer/RenderCmd.h"

// Temporary
#include "Platform/OpenGL/OpenGLShader.h"

namespace Spotlight
{

	struct Renderer2DData
	{
		Ref<VertexArray> QuadVAO;
		Ref<Shader> QuadShader;
	};

	static Renderer2DData *sm_Data;

	void Renderer2D::Init()
	{
		sm_Data = new Renderer2DData();
		sm_Data->QuadVAO = VertexArray::Create();

		float vertices[4 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		uint32_t indices[3 * 2] =
		{
			0, 1, 2,
			2, 3, 0
		};

		Ref<VertexBuffer> m_VBO = VertexBuffer::Create(vertices, sizeof(vertices));
		m_VBO->SetLayout({
			{ShaderDataType::Float3, "i_Position"}
		});
		sm_Data->QuadVAO->AddVertexBuffer(m_VBO);

		Ref<IndexBuffer> m_IBO = IndexBuffer::Create(indices, (uint32_t) std::size(indices));
		sm_Data->QuadVAO->SetIndexBuffer(m_IBO);

		sm_Data->QuadShader = Shader::Create("assets/Shaders/SolidColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete sm_Data;
	}

	void Renderer2D::BeginScene(const OrthoCamera &camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(sm_Data->QuadShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(sm_Data->QuadShader)->UploadUniformMat4("u_ViewProj", camera.GetViewProjMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(sm_Data->QuadShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}

	// Primitives

	void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(sm_Data->QuadShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(sm_Data->QuadShader)->UploadUniformFloat4("u_Color", color);

		sm_Data->QuadVAO->Bind();
		RenderCmd::DrawIndexed(sm_Data->QuadVAO);
	}

}