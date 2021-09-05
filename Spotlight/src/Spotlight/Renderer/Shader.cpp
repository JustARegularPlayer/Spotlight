#include "splpch.h"
#include "Shader.h"

#include "Spotlight/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Spotlight
{

	Ref<Shader> Shader::Create(const char* filepath)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:    SPL_CORE_ASSERT(false, "RendererAPI::None is currently selected!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(filepath);
		}

		SPL_CORE_ASSERT(false, "Unknown value. No Renderer API is selected!");
		return nullptr;
	}

}