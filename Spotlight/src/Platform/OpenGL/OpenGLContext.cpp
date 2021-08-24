#include "splpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Spotlight
{

	OpenGLContext::OpenGLContext(GLFWwindow* handle)
		: m_Handle(handle)
	{
		SPL_CORE_ASSERT(m_Handle, "The window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Handle);
		SPL_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Could not initialize Glad!");

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Handle);
	}

}