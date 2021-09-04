#pragma once

#include "Spotlight/Renderer/Shader.h"
#include <glm/glm.hpp>

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

		void UploadUniformInt(const std::string &name, int value);
		void UploadUniformFloat(const std::string &name, float value);
		void UploadUniformFloat2(const std::string &name, const glm::vec2 &values);
		void UploadUniformFloat3(const std::string &name, const glm::vec3 &values);
		void UploadUniformFloat4(const std::string &name, const glm::vec4 &values);
		void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
		void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);
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