#pragma once

#include "Spotlight/Core/Window.h"

#include <GLFW/glfw3.h>

namespace Spotlight
{

	class WinWindow : public Window
	{
	public:
		WinWindow(const WindowProperties& props);
		virtual ~WinWindow();

		virtual void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; };

		void SetEventCallback(const EventCallbackFunc& func) override { m_Data.EventCallback = func; }
		void SetVSync(bool isEnabled) override;
		bool IsVSync() const override;

	private:
		void Init();
		void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			EventCallbackFunc EventCallback;

			WindowData(const WindowProperties& props)
				: Title(props.Title), Width(props.Width), Height(props.Height), VSync(false), EventCallback(nullptr) {}
		};

		WindowData m_Data;
	};

}