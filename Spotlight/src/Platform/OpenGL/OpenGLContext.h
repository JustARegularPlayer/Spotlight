#pragma once

#include "Spotlight/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Spotlight
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* handle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Handle;
	};

}