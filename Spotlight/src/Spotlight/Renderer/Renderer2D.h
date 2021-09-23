#pragma once

#include "Spotlight/Renderer/OrthoCamera.h"
#include "Spotlight/Renderer/Texture.h"

namespace Spotlight
{

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthoCamera &camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2 &position, float angle, const glm::vec2 &size, const glm::vec4 &color);
		static void DrawQuad(const glm::vec3 &position, float angle, const glm::vec2 &size, const glm::vec4 &color);
		static void DrawQuad(const glm::vec2 &position, float angle, const glm::vec2 &size, const Ref<Texture2D> &texture, float tileCount = 1.0f);
		static void DrawQuad(const glm::vec3 &position, float angle, const glm::vec2 &size, const Ref<Texture2D> &texture, float tileCount = 1.0f);
	};

}