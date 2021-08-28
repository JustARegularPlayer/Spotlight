#pragma once

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
	private:
		ShaderSources ParseShader(const char* filepath);
		uint32_t CompileShader(const std::string& source, uint32_t type);
		uint32_t CreateProgram(std::string& vertexSource, std::string& fragSource);
	private:
		uint32_t m_ProgramID;
	};

}