#include "splpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Spotlight
{

	static const char *GLDebugToString(GLenum info)
	{
		switch (info)
		{
			case GL_DEBUG_SOURCE_API               : return "GL_DEBUG_SOURCE_API";               break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM     : return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";     break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER   : return "GL_DEBUG_SOURCE_SHADER_COMPILER";   break;
			case GL_DEBUG_SOURCE_THIRD_PARTY       : return "GL_DEBUG_SOURCE_THIRD_PARTY";       break;
			case GL_DEBUG_SOURCE_APPLICATION       : return "GL_DEBUG_SOURCE_APPLICATION";       break;
			case GL_DEBUG_SOURCE_OTHER             : return "GL_DEBUG_SOURCE_OTHER";             break;

			case GL_DEBUG_TYPE_ERROR               : return "GL_DEBUG_TYPE_ERROR";               break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR : return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR"; break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  : return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";  break;
			case GL_DEBUG_TYPE_PORTABILITY         : return "GL_DEBUG_TYPE_PORTABILITY";         break;
			case GL_DEBUG_TYPE_PERFORMANCE         : return "GL_DEBUG_TYPE_PERFORMANCE";         break;
			case GL_DEBUG_TYPE_OTHER               : return "GL_DEBUG_TYPE_OTHER";               break;

			case GL_DEBUG_TYPE_MARKER              : return "GL_DEBUG_TYPE_MARKER";              break;
			case GL_DEBUG_TYPE_PUSH_GROUP          : return "GL_DEBUG_TYPE_PUSH_GROUP";          break;
			case GL_DEBUG_TYPE_POP_GROUP           : return "GL_DEBUG_TYPE_POP_GROUP";           break;

			case GL_DEBUG_SEVERITY_HIGH            : return "GL_DEBUG_SEVERITY_HIGH";            break;
			case GL_DEBUG_SEVERITY_MEDIUM          : return "GL_DEBUG_SEVERITY_MEDIUM";          break;
			case GL_DEBUG_SEVERITY_LOW             : return "GL_DEBUG_SEVERITY_LOW";             break;
			case GL_DEBUG_SEVERITY_NOTIFICATION    : return "GL_DEBUG_SEVERITY_NOTIFICATION";    break;

			default                                : return "GL_DONT_CARE";
		}
	}

	static void APIENTRY OnError(GLenum source,
								 GLenum type,
								 GLuint id,
								 GLenum severity,
								 GLsizei length,
								 const GLchar *message,
								 const void *userParam)
	{
		if(type == GL_DEBUG_TYPE_ERROR)
			SPL_CORE_FATAL("OpenGL Error! :");

		SPL_CORE_ERROR("Source =   {}", GLDebugToString(source));
		SPL_CORE_ERROR("Type =     {}", GLDebugToString(type));
		SPL_CORE_ERROR("ID =       {}", id);
		SPL_CORE_ERROR("Severity = {}", GLDebugToString(severity));
		SPL_CORE_ERROR("Message:\n {}", message);

		if(severity == GL_DEBUG_SEVERITY_HIGH)
			SPL_CORE_ASSERT(false, "OpenGL error, high severity!");
	}
		
	OpenGLContext::OpenGLContext(GLFWwindow* handle)
		: m_Handle(handle)
	{
		SPL_CORE_ASSERT(m_Handle, "The window handle is null!");
	}

	void OpenGLContext::Init()
	{
		SPL_PROFILE_FUNC();

		glfwMakeContextCurrent(m_Handle);
		int success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		SPL_CORE_ASSERT(success, "Could not initialize Glad!");

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OnError, 0);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);

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