#pragma once

#include "RendererAPI.h"

namespace Spotlight
{

	class RenderCmd
	{
	public:
		inline static void Init()
		{
			sm_API->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			sm_API->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4 &color)
		{
			sm_API->SetClearColor(color);
		}

		inline static void Clear()
		{
			sm_API->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray> &vao, uint32_t count = 0)
		{
			sm_API->DrawIndexed(vao, count);
		}
	private:
		static RendererAPI *sm_API;
	};

}