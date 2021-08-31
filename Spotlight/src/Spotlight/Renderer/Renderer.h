#pragma once

#include "RenderCmd.h"

#include "Spotlight/Renderer/OrthoCamera.h"
#include "Spotlight/Renderer/Shader.h"

namespace Spotlight
{

	class Renderer
	{
	public:
		static void BeginScene(OrthoCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader,
						   const std::shared_ptr<VertexArray> &vao);

		static inline RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjMatrix;
		};
		static SceneData *sm_SceneData;
	};

}