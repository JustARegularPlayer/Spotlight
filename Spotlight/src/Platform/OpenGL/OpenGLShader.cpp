#include "splpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Spotlight
{

	static GLenum StringToGLenum(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		SPL_CORE_ASSERT(false, "Shader type \"{}\" is unknown!", "#shader " + type);
		return 0;
	}

	OpenGLShader::OpenGLShader(const  std::string &filepath)
		: m_ProgramID(0)
	{
		std::string src = ParseFile(filepath);
		auto shaderSources = Preprocess(src);
		m_ProgramID = CreateProgram(shaderSources);

		std::filesystem::path path = filepath;
		m_Name = path.stem().string();
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string &vertex, const std::string &fragment)
		: m_ProgramID(0), m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertex;
		sources[GL_FRAGMENT_SHADER] = fragment;
		m_ProgramID = CreateProgram(sources);
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

	std::string OpenGLShader::ParseFile(const std::string &filepath)
	{
		std::ifstream file(filepath, std::ios::in | std::ios::binary);
		std::string source;

		if (!file.is_open())
		{
			file.close();
			SPL_CORE_WARN("File \"{}\" cannot be opened!", filepath);
		}
		else
		{
			file.seekg(0, std::ios::end);
			source.resize(file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&source[0], source.size());
			file.close();
		}

		return source;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string &src)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char *typeToken = "#shader";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = src.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t begin = pos + typeTokenLength + 1;
			size_t eol = src.find_first_of("\r\n", pos);
			SPL_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
			
			std::string shaderType = src.substr(begin, eol - begin);
			SPL_CORE_ASSERT(StringToGLenum(shaderType), "Specified shader type is invalid!");

			size_t nextLinePos = src.find_first_not_of("\r\n", eol);
			pos = src.find(typeToken, nextLinePos);
			shaderSources[StringToGLenum(shaderType)] = 
				src.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? src.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	uint32_t OpenGLShader::CompileShader(GLenum type, const std::string& shaderSource)
	{
		const char* src = shaderSource.c_str(); // convert std::string to a const char* since OpenGL won't accept
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

	uint32_t OpenGLShader::CreateProgram(const std::unordered_map<GLenum, std::string> sources)
	{
		SPL_CORE_ASSERT(sources.size() <= 2, "Too many shader sources!");
		uint32_t program = glCreateProgram();
		std::array<uint32_t, 2> shaderIDs;
		int glShaderIndex = 0;
		for (auto &[key, value] : sources)
		{
			uint32_t shader = CompileShader(key, value);
			glAttachShader(program, shader);
			shaderIDs[glShaderIndex++] = shader;
		}

		glLinkProgram(program);
		glValidateProgram(program);

		for (uint32_t shader : shaderIDs)
		{
			glDetachShader(m_ProgramID, shader);
			glDeleteShader(shader);
		}
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