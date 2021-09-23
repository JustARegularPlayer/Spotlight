#pragma once

#include "Spotlight/Renderer/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

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
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertex, const std::string& fragment);
		virtual	~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string &name, int value) override;
		virtual void SetFloat(const std::string &name, float value) override;
		virtual void SetFloat2(const std::string &name, const glm::vec2 &values) override;
		virtual void SetFloat3(const std::string &name, const glm::vec3 &values) override;
		virtual void SetFloat4(const std::string &name, const glm::vec4 &values) override;
		virtual void SetMat4(const std::string &name, const glm::mat4 &matrix) override;

		virtual const std::string &GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string &name, int value);
		void UploadUniformFloat(const std::string &name, float value);
		void UploadUniformFloat2(const std::string &name, const glm::vec2 &values);
		void UploadUniformFloat3(const std::string &name, const glm::vec3 &values);
		void UploadUniformFloat4(const std::string &name, const glm::vec4 &values);
		void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
		void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);
	private:
		std::string ParseFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& src);
		uint32_t CompileShader(GLenum type, const std::string& shaderSource);
		uint32_t CreateProgram(const std::unordered_map<GLenum, std::string> sources);

		int GetUniformLocation(const std::string& name);
	private:
		uint32_t m_ProgramID;
		std::string m_Name;
		std::unordered_map<std::string, int> m_UniformLocations;
	};

}