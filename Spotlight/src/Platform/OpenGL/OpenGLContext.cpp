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
		int success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		SPL_CORE_ASSERT(success, "Could not initialize Glad!");

		SPL_CORE_INFO("OpenGL Driver Details:");
		SPL_CORE_INFO("\t- Vendor: {}", glGetString(GL_VENDOR));
		SPL_CORE_INFO("\t- Renderer: {}", glGetString(GL_RENDERER));
		SPL_CORE_INFO("\t- Version: {}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Handle);
	}

}