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
		SPL_PROFILE_FUNC();

		sm_Data = new Renderer2DData();
		sm_Data->QuadVAO = VertexArray::Create();

		float quadVertices[4 * 5] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t quadIndices[3 * 2] =
		{
			0, 1, 2,
			2, 3, 0
		};

		Ref<VertexBuffer> m_VBO = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		m_VBO->SetLayout({
			{ShaderDataType::Float3, "i_Position"},
			{ShaderDataType::Float2, "i_TexCoord"}
		});
		sm_Data->QuadVAO->AddVertexBuffer(m_VBO);

		Ref<IndexBuffer> m_IBO = IndexBuffer::Create(quadIndices, (uint32_t) std::size(quadIndices));
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
		SPL_PROFILE_FUNC();

		delete sm_Data;
	}

	void Renderer2D::BeginScene(const OrthoCamera &camera)
	{
		SPL_PROFILE_FUNC();

		sm_Data->QuadShader->Bind();
		sm_Data->QuadShader->SetMat4("u_ViewProj", camera.GetViewProjMatrix());
	}

	void Renderer2D::EndScene()
	{
		SPL_PROFILE_FUNC();
	}

	// Primitives //////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// - Quad ---------------------------------------------------------------------------------------------

	void Renderer2D::DrawQuad(const ColorQuad &quad)
	{
		SPL_PROFILE_FUNC();

		sm_Data->QuadShader->Bind();
		sm_Data->QuadShader->SetFloat4("u_Color", quad.Color);
		sm_Data->BlankTexture->Bind();

		{
			SPL_PROFILE_SCOPE("Transform Matrix Computation - Renderer2D::DrawQuad()");

			glm::mat4 Transform = glm::translate(glm::mat4(1.0f), quad.Position);                // Position
			Transform = glm::rotate(Transform, glm::radians(quad.Rotation), glm::vec3(0, 0, 1)); // Position * Rotation
			Transform = glm::scale(Transform, {quad.Scale.x, quad.Scale.y, 1.0f});               // Position * Rotation * Scale (Process done)
			sm_Data->QuadShader->SetMat4("u_Transform", Transform);                              // Send to QuadShader
		}

		sm_Data->QuadVAO->Bind();
		RenderCmd::DrawIndexed(sm_Data->QuadVAO);
	}

	void Renderer2D::DrawQuad(const TextureQuad &quad)
	{
		SPL_PROFILE_FUNC();

		sm_Data->QuadShader->Bind();
		sm_Data->QuadShader->SetFloat4("u_Color", quad.Tint);
		quad.Texture->Bind();

		{
			SPL_PROFILE_SCOPE("Transform Matrix Computation - Renderer2D::DrawQuad()");

			glm::mat4 Transform = glm::translate(glm::mat4(1.0f), quad.Position);                // Position
			Transform = glm::rotate(Transform, glm::radians(quad.Rotation), glm::vec3(0, 0, 1)); // Position * Rotation
			Transform = glm::scale(Transform, {quad.Scale.x, quad.Scale.y, 1.0f});               // Position * Rotation * Scale (Process done)
			sm_Data->QuadShader->SetMat4("u_Transform", Transform);                              // Send to QuadShader
			sm_Data->QuadShader->SetFloat("u_TileFactor", quad.TileFactor);
		}

		sm_Data->QuadVAO->Bind();
		RenderCmd::DrawIndexed(sm_Data->QuadVAO);
	}

}