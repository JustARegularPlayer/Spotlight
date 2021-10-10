#pragma once

#include "Spotlight/Renderer/OrthoCamera.h"
#include "Spotlight/Renderer/Texture.h"

namespace Spotlight
{
	// Primitive structs for parameters
	struct ColorQuad;
	struct TextureQuad;

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthoCamera &camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const ColorQuad &quad);     // Quads
		static void DrawQuad(const TextureQuad &quad);
	};

	struct ColorQuad
	{
		glm::vec3 Position;
		float Rotation;
		glm::vec2 Scale;
		glm::vec4 Color;
	};

	struct TextureQuad
	{
		glm::vec3 Position;
		float Rotation;
		glm::vec2 Scale;

		Ref<Texture2D> Texture;
		float TileFactor = 1.0f;

		glm::vec4 Tint = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

}