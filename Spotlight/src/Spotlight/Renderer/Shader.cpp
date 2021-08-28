#include "splpch.h"
#include "Shader.h"

#include "Spotlight/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Spotlight
{

	Shader* Shader::Create(const char* filepath)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::None:		SPL_CORE_ASSERT(false, "RendererAPI::None is currently selected!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLShader(filepath);
		}

		SPL_CORE_ASSERT(false, "Unknown value. No Renderer API is selected!");
		return nullptr;
	}

}