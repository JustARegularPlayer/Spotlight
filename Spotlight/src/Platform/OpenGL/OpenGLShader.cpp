#include "splpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

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

	// SHADER PROGRAM CREATION ==================================================================

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
				if (line.find("vertex") != std::string::npos)	// if the read line is "#shader vertex",
				{												// set type into 0
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)	// if line is "#shader fragment",
				{														// set type into 1
					type = ShaderType::FRAGMENT;
				}
			}
			else
			{
				ss[(int)type] << line << std::endl;	// ss[0] - Vertex shader source
			}										// ss[1] - Fragment shader source
		}

		file.close();
		return {ss[0].str(), ss[1].str()};
	}

	uint32_t OpenGLShader::CompileShader(const std::string& source, uint32_t type)
	{
		const char* src = source.c_str(); // convert std::string to a const char* since OpenGL won't accept
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
			SPL_CORE_ASSERT(false, "OpenGL shader compilation error! (See message above for details)");
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

	// UNIFORMS =================================================================================

	void OpenGLShader::UploadUniformInt(const std::string &name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string &name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &values)
	{
		glUniform2f(GetUniformLocation(name), values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &values)
	{
		glUniform3f(GetUniformLocation(name), values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		glUniform4f(GetUniformLocation(name), values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocations.find(name) != m_UniformLocations.end())
			return m_UniformLocations[name];

		// If a uniform location is not currently saved in the map, get the location and save it.
		int location = glGetUniformLocation(m_ProgramID, name.c_str());
		m_UniformLocations[name] = location;

		// If it does not exist, just warn the user. The missing location won't kill the program.
		if (location == -1)
			SPL_CORE_WARN("A shader uniform location cannot be found: {}", name);

		return location;
	}

}