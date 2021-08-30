#pragma once

#include "RendererAPI.h"

namespace Spotlight
{

	class RenderCmd
	{
	public:
		inline static void SetClearColor(const glm::vec4 &color)
		{
			sm_API->SetClearColor(color);
		}

		inline static void Clear()
		{
			sm_API->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray> &vao)
		{
			sm_API->DrawIndexed(vao);
		}
	private:
		static RendererAPI *sm_API;
	};

}