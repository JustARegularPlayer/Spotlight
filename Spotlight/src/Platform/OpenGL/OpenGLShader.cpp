#include "splpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Spotlight
{

	OpenGLShader::OpenGLShader(const char* filepath)
		: m_ProgramID(0)
	{
		ShaderSources src = ParseShader(filepath);
		m_ProgramID = CreateProgram(src.VertexSrc, src.FragSrc);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ProgramID);
	}
	
	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ProgramID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	ShaderSources OpenGLShader::ParseShader(const char* filepath)
	{
		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::ifstream file(filepath);
		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		SPL_CORE_ASSERT(file.is_open(), "File cannot be opened!");

		while (getline(file, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
				}
			}
			else
			{
				ss[(int)type] << line << std::endl;
			}
		}

		file.close();
		return {ss[0].str(), ss[1].str()};
	}

	uint32_t OpenGLShader::CompileShader(const std::string& source, uint32_t type)
	{
		const char* src = source.c_str();
		uint32_t shader = glCreateShader(type);
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			int length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> log(length);
			glGetShaderInfoLog(shader, length, &length, &log[0]);

			SPL_ERROR("Shader type: {}", (type == GL_VERTEX_SHADER ? "VertexShader" : "FragmentShader"));
			SPL_ERROR("\t- {}", &log[0]);
			SPL_CORE_ASSERT(false, "OpenGL shader compilation error!");
		}
		return shader;
	}

	uint32_t OpenGLShader::CreateProgram(std::string& vertexSource, std::string& fragSource)
	{
		uint32_t program = glCreateProgram();
		uint32_t vs = CompileShader(vertexSource, GL_VERTEX_SHADER);
		uint32_t fs = CompileShader(fragSource, GL_FRAGMENT_SHADER);
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
}