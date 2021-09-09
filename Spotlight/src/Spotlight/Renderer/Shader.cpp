#include "splpch.h"
#include "Shader.h"

#include "Spotlight/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Spotlight
{

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:    SPL_CORE_ASSERT(false, "RendererAPI::None is currently selected!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(filepath);
		}

		SPL_CORE_ASSERT(false, "Unknown value. No Renderer API is selected!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string &vertex, const std::string &fragment)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:    SPL_CORE_ASSERT(false, "RendererAPI::None is currently selected!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(vertex, fragment);
		}

		SPL_CORE_ASSERT(false, "Unknown value. No Renderer API is selected!");
		return nullptr;
	}

}