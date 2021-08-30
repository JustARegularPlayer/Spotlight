#pragma once

#include "RenderCmd.h"

namespace Spotlight
{

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vao);

		static inline RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }
	};

}