#pragma once

#include "splpch.h"

namespace Spotlight
{

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {}

		static Shader* Create(const char* filepath);
	};

}