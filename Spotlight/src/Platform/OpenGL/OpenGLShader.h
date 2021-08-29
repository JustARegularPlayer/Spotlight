#pragma once

#include "splpch.h"
#include "Spotlight/Renderer/Shader.h"

namespace Spotlight
{

	struct ShaderSources
	{
		std::string VertexSrc;
		std::string FragSrc;
	};

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* filepath);
		virtual	~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;
	private:
		ShaderSources ParseShader(const char* filepath);
		uint32_t CompileShader(const std::string& source, uint32_t type);
		uint32_t CreateProgram(std::string& vertexSource, std::string& fragSource);

		int GetUniformLocation(const std::string& name);
	private:
		uint32_t m_ProgramID;
		std::unordered_map<std::string, int> m_UniformLocations;
	};

}