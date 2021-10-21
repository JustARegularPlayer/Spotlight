#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace Spotlight
{

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string &name, int32_t value) = 0;
		virtual void SetInt2(const std::string &name, glm::ivec2 values) = 0;
		virtual void SetInt3(const std::string &name, glm::ivec3 values) = 0;
		virtual void SetInt4(const std::string &name, glm::ivec4 values) = 0;
		virtual void SetIntArray(const std::string &name, uint32_t count, int32_t *values) = 0;
		virtual void SetUInt(const std::string &name, uint32_t value) = 0;
		virtual void SetUInt2(const std::string &name, glm::uvec2 values) = 0;
		virtual void SetUInt3(const std::string &name, glm::uvec3 values) = 0;
		virtual void SetUInt4(const std::string &name, glm::uvec4 values) = 0;
		virtual void SetUIntArray(const std::string &name, uint32_t count, uint32_t *values) = 0;
		virtual void SetFloat(const std::string &name, float value) = 0;
		virtual void SetFloat2(const std::string &name, const glm::vec2 &values) = 0;
		virtual void SetFloat3(const std::string &name, const glm::vec3 &values) = 0;
		virtual void SetFloat4(const std::string &name, const glm::vec4 &values) = 0;
		virtual void SetMat3(const std::string &name, const glm::mat3 &matrix) = 0;
		virtual void SetMat4(const std::string &name, const glm::mat4 &matrix) = 0;

		virtual const std::string &GetName() const = 0;

		static Ref<Shader> Create(const std::string &filepath);
		static Ref<Shader> Create(const std::string &name, const std::string &vertex, const std::string &fragment);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string &name, const Ref<Shader> &shader);
		void Add(const Ref<Shader> &shader);
		Ref<Shader> Load(const std::string &name, const std::string &filepath);
		Ref<Shader> Load(const std::string &filepath);

		Ref<Shader> Get(const std::string &name);
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}