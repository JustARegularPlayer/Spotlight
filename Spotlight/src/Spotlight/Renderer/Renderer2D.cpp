#include "splpch.h"
#include "Renderer2D.h"

#include "Spotlight/Renderer/VertexArray.h"
#include "Spotlight/Renderer/Shader.h"

#include "Spotlight/Renderer/RenderCmd.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Spotlight
{

	struct Renderer2DData
	{
		Ref<VertexArray> QuadVAO;
		Ref<Shader> QuadShader;
		Ref<Texture2D> BlankTexture;
	};

	static Renderer2DData *sm_Data;

	void Renderer2D::Init()
	{
		sm_Data = new Renderer2DData();
		sm_Data->QuadVAO = VertexArray::Create();

		float vertices[4 * 5] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t indices[3 * 2] =
		{
			0, 1, 2,
			2, 3, 0
		};

		Ref<VertexBuffer> m_VBO = VertexBuffer::Create(vertices, sizeof(vertices));
		m_VBO->SetLayout({
			{ShaderDataType::Float3, "i_Position"},
			{ShaderDataType::Float2, "i_TexCoord"}
		});
		sm_Data->QuadVAO->AddVertexBuffer(m_VBO);

		Ref<IndexBuffer> m_IBO = IndexBuffer::Create(indices, (uint32_t) std::size(indices));
		sm_Data->QuadVAO->SetIndexBuffer(m_IBO);

		sm_Data->BlankTexture = Texture2D::Create(1, 1);
		uint32_t whiteTexData = 0xffffffff;
		sm_Data->BlankTexture->SetData(&whiteTexData, sizeof(uint32_t));

		sm_Data->QuadShader = Shader::Create("assets/Shaders/Texture.glsl");
		sm_Data->QuadShader->Bind();
		sm_Data->QuadShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete sm_Data;
	}

	void Renderer2D::BeginScene(const OrthoCamera &camera)
	{
		sm_Data->QuadShader->Bind();
		sm_Data->QuadShader->SetMat4("u_ViewProj", camera.GetViewProjMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	// Primitives

	void Renderer2D::DrawQuad(const glm::vec2 &position, float angle, const glm::vec2 &size, const glm::vec4 &color)
	{
		DrawQuad({position.x, position.y, 0.0f}, angle, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &position, float angle, const glm::vec2 &size, const glm::vec4 &color)
	{
		sm_Data->QuadShader->Bind();
		sm_Data->QuadShader->SetFloat4("u_Color", color);
		sm_Data->BlankTexture->Bind();

		glm::mat4 T = glm::translate(glm::mat4(1.0f), position);                // Transform
		glm::mat4 TR = glm::rotate(T, glm::radians(angle), glm::vec3(0, 0, 1)); // Transform * Rotation (no S yet)
		glm::mat4 TRS = glm::scale(TR, {size.x, size.y, 1.0f});                 // Transform * Rotation * Scale (Process done)
		sm_Data->QuadShader->SetMat4("u_Transform", TRS);                       // Send to SolidColorShader

		sm_Data->QuadVAO->Bind();
		RenderCmd::DrawIndexed(sm_Data->QuadVAO);
	}

	void Renderer2D::DrawQuad(const glm::vec2 &position, float angle, const glm::vec2 &size, const Ref<Texture2D> &texture, float texScale)
	{
		DrawQuad({position.x, position.y, 0.0f}, angle, size, texture, texScale);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &position, float angle, const glm::vec2 &size, const Ref<Texture2D> &texture, float texScale)
	{
		sm_Data->QuadShader->Bind();
		sm_Data->QuadShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 T = glm::translate(glm::mat4(1.0f), position);                // Transform
		glm::mat4 TR = glm::rotate(T, glm::radians(angle), glm::vec3(0, 0, 1)); // Transform * Rotation (no S yet)
		glm::mat4 TRS = glm::scale(TR, {size.x, size.y, 1.0f});                 // Transform * Rotation * Scale (Process done)
		sm_Data->QuadShader->SetMat4("u_Transform", TRS);                    // Send to TextureShader
		sm_Data->QuadShader->SetFloat("u_TexScale", texScale);

		sm_Data->QuadVAO->Bind();
		RenderCmd::DrawIndexed(sm_Data->QuadVAO);
	}

}