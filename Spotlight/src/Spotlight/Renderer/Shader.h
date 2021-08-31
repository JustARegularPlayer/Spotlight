#pragma once

#include "splpch.h"
#include <glm/glm.hpp>

namespace Spotlight
{

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {}
		virtual void UploadUniformMat4(const std::string &name, const glm::mat4& matrix) {}

		static Shader* Create(const char* filepath);
	};

}