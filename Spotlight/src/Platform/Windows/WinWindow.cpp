#include "splpch.h"
#include "WinWindow.h"

#include "Spotlight/Events/AppEvent.h"
#include "Spotlight/Events/KeyEvent.h"
#include "Spotlight/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Spotlight
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char *description)
	{
		SPL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Scope<Window> Window::Create(const WindowProperties &props)
	{
		return CreateScope<WinWindow>(props);
	}

	WinWindow::WinWindow(const WindowProperties &props)
		: m_Data(props)
	{
		SPL_PROFILE_FUNC();

		Init();
	}

	WinWindow::~WinWindow()
	{
		SPL_PROFILE_FUNC();

		Shutdown();
		if (s_GLFWInitialized)
		{
			glfwTerminate();
			s_GLFWInitialized = false;
		}
	}

	void WinWindow::Init()
	{
		SPL_PROFILE_FUNC();

		if (!s_GLFWInitialized)
		{
			SPL_PROFILE_SCOPE("glfwInit()");

			SPL_CORE_ASSERT(glfwInit(), "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		SPL_CORE_INFO("Creating {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);
		{
			SPL_PROFILE_SCOPE("glfwCreateWindow");

			m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		}
		{
			SPL_PROFILE_SCOPE("new OpenGLContext");

			m_Context = new OpenGLContext(m_Window);
			m_Context->Init();
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
				Event_WindowClosed e;
				data.EventCallback(e);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
			{
				WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				Event_WindowResized e(width, height);
				data.EventCallback(e);
			});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xPos, int yPos)
			{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
				Event_WindowMoved e(xPos, yPos);
				data.xPos = xPos;
				data.yPos = yPos;

				data.EventCallback(e);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int keycode, int scancode, int action, int mods)
			{
				WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						Event_KeyPressed e(keycode, 0);
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						Event_KeyReleased e(keycode);
						data.EventCallback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						Event_KeyPressed e(keycode, 1);
						data.EventCallback(e);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode)
			{
				WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
				Event_CharTyped e(keycode);
				data.EventCallback(e);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos)
			{
				WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
				Event_MouseMoved e((float)xPos, (float)yPos);
				data.EventCallback(e);
			});
		
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
			{
				WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
					case GLFW_PRESS:
					{
						Event_MouseButtonPressed e(button);
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						Event_MouseButtonReleased e(button);
						data.EventCallback(e);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset)
			{
				WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
				Event_MouseScrolled e((float)xOffset, (float)yOffset);
				data.EventCallback(e);
			});

	}

	void WinWindow::Shutdown()
	{
		SPL_PROFILE_FUNC();

		glfwDestroyWindow(m_Window);
	}

	void WinWindow::OnUpdate()
	{
		SPL_PROFILE_FUNC();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WinWindow::SetVSync(bool isEnabled)
	{
		SPL_PROFILE_FUNC();

		if (isEnabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = isEnabled;
	}

}