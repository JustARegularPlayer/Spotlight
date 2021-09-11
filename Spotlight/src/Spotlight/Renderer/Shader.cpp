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

	Ref<Shader> Shader::Create(const std::string &name, const std::string &vertex, const std::string &fragment)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:    SPL_CORE_ASSERT(false, "RendererAPI::None is currently selected!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name, vertex, fragment);
		}

		SPL_CORE_ASSERT(false, "Unknown value. No Renderer API is selected!");
		return nullptr;
	}

	// Add shader to library
	
	void ShaderLibrary::Add(const std::string &name, const Ref<Shader> &shader)
	{
		SPL_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader is already added to the library!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader> &shader)
	{
		auto &name = shader->GetName();
		Add(name, shader);
	}

	// Load shader

	Ref<Shader> ShaderLibrary::Load(const std::string &name, const std::string &filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}


	Ref<Shader> ShaderLibrary::Load(const std::string &filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string &name)
	{
		SPL_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found!");
		return m_Shaders[name];
	}

}