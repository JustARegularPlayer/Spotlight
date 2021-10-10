#include "splpch.h"
#include "Renderer2D.h"

#include "Spotlight/Renderer/VertexArray.h"
#include "Spotlight/Renderer/Shader.h"

#include "Spotlight/Renderer/RenderCmd.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Spotlight
{

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		Ref<VertexArray> QuadVAO;
		Ref<VertexBuffer> QuadVBO;
		Ref<Shader> QuadShader;
		Ref<Texture2D> BlankTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex *QuadVertexBufferLowerBound = nullptr;
		QuadVertex *QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		SPL_PROFILE_FUNC();

		s_Data.QuadVAO = VertexArray::Create();

		s_Data.QuadVBO = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVBO->SetLayout({
			{ShaderDataType::Float3, "i_Position"},
			{ShaderDataType::Float4, "i_Color"},
			{ShaderDataType::Float2, "i_TexCoord"}
		});
		s_Data.QuadVAO->AddVertexBuffer(s_Data.QuadVBO);

		// Dynamic array of vertices.
		s_Data.QuadVertexBufferLowerBound = new QuadVertex[s_Data.MaxVertices];

		// Static array of indices.
		uint32_t *quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 0;
			quadIndices[i + 4] = offset + 2;
			quadIndices[i + 5] = offset + 3;

			offset += 4;
		}
		
		Ref<IndexBuffer> quadIBO = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVAO->SetIndexBuffer(quadIBO);
		delete[] quadIndices;
		// Delete static array of indices.

		s_Data.BlankTexture = Texture2D::Create(1, 1);
		uint32_t whiteTexData = 0xffffffff;
		s_Data.BlankTexture->Bind(0);
		s_Data.BlankTexture->SetData(&whiteTexData, sizeof(uint32_t));

		s_Data.QuadShader = Shader::Create("assets/Shaders/Texture.glsl");
		s_Data.QuadShader->Bind();
		//s_Data.QuadShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		SPL_PROFILE_FUNC();
	}

	void Renderer2D::BeginScene(const OrthoCamera &camera)
	{
		SPL_PROFILE_FUNC();

		s_Data.QuadShader->Bind();
		s_Data.QuadShader->SetMat4("u_ViewProj", camera.GetViewProjMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferLowerBound;
	}

	void Renderer2D::EndScene()
	{
		SPL_PROFILE_FUNC();
		
		// Get the size of data in bytes rather than, by default, the amount of vertices.
		size_t dataSize = (uint8_t *)s_Data.QuadVertexBufferPtr - (uint8_t *)s_Data.QuadVertexBufferLowerBound;
		s_Data.QuadVBO->SetData(s_Data.QuadVertexBufferLowerBound, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		SPL_PROFILE_FUNC();

		RenderCmd::DrawIndexed(s_Data.QuadVAO, s_Data.QuadIndexCount);
	}

	// Primitives //////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// - Quad ---------------------------------------------------------------------------------------------

	void Renderer2D::DrawQuad(const ColorQuad &quad)
	{
		SPL_PROFILE_FUNC();

		s_Data.QuadVertexBufferPtr->Position = quad.Position;
		s_Data.QuadVertexBufferPtr->Color = quad.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;
		
		s_Data.QuadVertexBufferPtr->Position = { quad.Position.x + quad.Scale.x, quad.Position.y, quad.Position.z };
		s_Data.QuadVertexBufferPtr->Color = quad.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;
		
		s_Data.QuadVertexBufferPtr->Position =  { quad.Position.x + quad.Scale.x, quad.Position.y + quad.Scale.y, quad.Position.z };
		s_Data.QuadVertexBufferPtr->Color = quad.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;
		
		s_Data.QuadVertexBufferPtr->Position =  { quad.Position.x, quad.Position.y + quad.Scale.y, quad.Position.z };
		s_Data.QuadVertexBufferPtr->Color = quad.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;
		
		/*
		s_Data.BlankTexture->Bind();
		{
			SPL_PROFILE_SCOPE("Transform Matrix Computation - Renderer2D::DrawQuad()");

			glm::mat4 Transform = glm::translate(glm::mat4(1.0f), quad.Position);                // Position
			Transform = glm::rotate(Transform, glm::radians(quad.Rotation), glm::vec3(0, 0, 1)); // Position * Rotation
			Transform = glm::scale(Transform, {quad.Scale.x, quad.Scale.y, 1.0f});               // Position * Rotation * Scale (Process done)
			s_Data.QuadShader->SetMat4("u_Transform", Transform);                                // Send to QuadShader
		}

		s_Data.QuadVAO->Bind();
		RenderCmd::DrawIndexed(s_Data.QuadVAO);
		*/
	}

	void Renderer2D::DrawQuad(const TextureQuad &quad)
	{
		SPL_PROFILE_FUNC();

		s_Data.QuadVertexBufferPtr->Position = quad.Position;
		s_Data.QuadVertexBufferPtr->Color = quad.Tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { quad.Position.x + quad.Scale.x, quad.Position.y, quad.Position.z };
		s_Data.QuadVertexBufferPtr->Color = quad.Tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f * quad.TileFactor, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position =  { quad.Position.x + quad.Scale.x, quad.Position.y + quad.Scale.y, quad.Position.z };
		s_Data.QuadVertexBufferPtr->Color = quad.Tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f * quad.TileFactor, 1.0f * quad.TileFactor };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position =  { quad.Position.x, quad.Position.y + quad.Scale.y, quad.Position.z };
		s_Data.QuadVertexBufferPtr->Color = quad.Tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f * quad.TileFactor };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		/*
		quad.Texture->Bind(0);

		{
			SPL_PROFILE_SCOPE("Transform Matrix Computation - Renderer2D::DrawQuad()");

			glm::mat4 Transform = glm::translate(glm::mat4(1.0f), quad.Position);                // Position
			Transform = glm::rotate(Transform, glm::radians(quad.Rotation), glm::vec3(0, 0, 1)); // Position * Rotation
			Transform = glm::scale(Transform, {quad.Scale.x, quad.Scale.y, 1.0f});               // Position * Rotation * Scale (Process done)
			s_Data.QuadShader->SetMat4("u_Transform", Transform);                                // Send to QuadShader
			s_Data.QuadShader->SetFloat("u_TileFactor", quad.TileFactor);
		}

		s_Data.QuadVAO->Bind();
		RenderCmd::DrawIndexed(s_Data.QuadVAO);
		*/
	}

}