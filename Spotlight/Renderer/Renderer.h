#pragma once

#include "RenderCmd.h"

#include "Spotlight/Renderer/OrthoCamera.h"
#include "Spotlight/Renderer/Shader.h"

namespace Spotlight
{

	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResized(uint32_t width, uint32_t height);

		static void BeginScene(OrthoCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,
						   const Ref<VertexArray> &vao,
						   const glm::mat4& transform = glm::mat4(1.0f));

		static inline RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjMatrix;
		};
		static SceneData *sm_SceneData;
	};

}