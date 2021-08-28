#pragma once

namespace Spotlight
{

	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		static inline RendererAPI GetCurrentAPI() { return sm_RendererAPI; }
	private:
		static RendererAPI sm_RendererAPI;
	};

}