#pragma once

#include <glm/glm.hpp>
#include "Spotlight/Renderer/VertexArray.h"

namespace Spotlight
{

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		static API GetAPI() { return sm_API; }

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vao) = 0;
	private:
		static API sm_API;
	};

}