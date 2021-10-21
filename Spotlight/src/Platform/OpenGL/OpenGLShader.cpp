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
		SPL_PROFILE_FUNC();

		std::string src = ParseFile(filepath);
		auto shaderSources = Preprocess(src);
		m_ProgramID = CreateProgram(shaderSources);

		std::filesystem::path path = filepath;
		m_Name = path.stem().string();
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string &vertex, const std::string &fragment)
		: m_ProgramID(0), m_Name(name)
	{
		SPL_PROFILE_FUNC();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertex;
		sources[GL_FRAGMENT_SHADER] = fragment;
		m_ProgramID = CreateProgram(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		SPL_PROFILE_FUNC();

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

	void OpenGLShader::SetInt(const std::string &name, int32_t value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetInt2(const std::string &name, glm::ivec2 values)
	{
		UploadUniformInt2(name, values);
	}

	void OpenGLShader::SetInt3(const std::string & name, glm::ivec3 values)
	{
		UploadUniformInt3(name, values);
	}

	void OpenGLShader::SetInt4(const std::string & name, glm::ivec4 values)
	{
		UploadUniformInt4(name, values);
	}

	void OpenGLShader::SetIntArray(const std::string &name, uint32_t count, int32_t *values)
	{
		UploadUniformIntArray(name, count, values);
	}

	void OpenGLShader::SetUInt(const std::string &name, uint32_t value)
	{
		UploadUniformUInt(name, value);
	}

	void OpenGLShader::SetUInt2(const std::string & name, glm::uvec2 values)
	{
		UploadUniformUInt2(name, values);
	}

	void OpenGLShader::SetUInt3(const std::string & name, glm::uvec3 values)
	{
		UploadUniformUInt3(name, values);
	}

	void OpenGLShader::SetUInt4(const std::string & name, glm::uvec4 values)
	{
		UploadUniformUInt4(name, values);
	}

	void OpenGLShader::SetUIntArray(const std::string & name, uint32_t count, uint32_t * values)
	{
		UploadUniformUIntArray(name, count, values);
	}

	void OpenGLShader::SetFloat(const std::string &name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string &name, const glm::vec2 &values)
	{
		UploadUniformFloat2(name, values);
	}

	void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &values)
	{
		UploadUniformFloat3(name, values);
	}

	void OpenGLShader::SetFloat4(const std::string &name, const glm::vec4 &values)
	{
		UploadUniformFloat4(name, values);
	}

	void OpenGLShader::SetMat3(const std::string &name, const glm::mat3 &matrix)
	{
		UploadUniformMat3(name, matrix);
	}

	void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &matrix)
	{
		UploadUniformMat4(name, matrix);
	}

	// SHADER PROGRAM CREATION ==================================================================

	std::string OpenGLShader::ParseFile(const std::string &filepath)
	{
		SPL_PROFILE_FUNC();

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
		SPL_PROFILE_FUNC();

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
		SPL_PROFILE_FUNC();

		const char* src = shaderSource.c_str(); // convert std::string to a const char* since OpenGL won't accept
		uint32_t shader = glCreateShader(type);
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);
		return shader;
	}

	uint32_t OpenGLShader::CreateProgram(const std::unordered_map<GLenum, std::string> sources)
	{
		SPL_PROFILE_FUNC();

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
			glDetachShader(program, shader);
			glDeleteShader(shader);
		}
		return program;
	}

	// UNIFORMS =================================================================================

	void OpenGLShader::UploadUniformInt(const std::string &name, int32_t value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformInt2(const std::string &name, const glm::ivec2 values)
	{
		glUniform2i(GetUniformLocation(name), values.x, values.y);
	}

	void OpenGLShader::UploadUniformInt3(const std::string & name, const glm::ivec3 values)
	{
		glUniform3i(GetUniformLocation(name), values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformInt4(const std::string & name, const glm::ivec4 values)
	{
		glUniform4i(GetUniformLocation(name), values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string &name, uint32_t count, int32_t *values)
	{
		glUniform1iv(GetUniformLocation(name), count, values);
	}

	void OpenGLShader::UploadUniformUInt(const std::string &name, uint32_t value)
	{
		glUniform1ui(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformUInt2(const std::string & name, const glm::uvec2 values)
	{
		glUniform2ui(GetUniformLocation(name), values.x, values.y);
	}

	void OpenGLShader::UploadUniformUInt3(const std::string & name, const glm::uvec3 values)
	{
		glUniform3ui(GetUniformLocation(name), values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformUInt4(const std::string & name, const glm::uvec4 values)
	{
		glUniform4ui(GetUniformLocation(name), values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformUIntArray(const std::string & name, uint32_t count, uint32_t * values)
	{
		glUniform1uiv(GetUniformLocation(name), count, values);
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