#pragma once

#include "Spotlight/Core/Window.h"
#include "Spotlight/Renderer/GraphicsContext.h"

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
		bool inline IsVSync() const override { return m_Data.VSync; }

		virtual inline void* GetNativeWindow() const { return m_Window; }
	private:
		void Init();
		void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			int xPos;
			int yPos;
			bool VSync;
			EventCallbackFunc EventCallback;

			WindowData(const WindowProperties& props)
				: Title(props.Title), Width(props.Width), Height(props.Height), xPos(0), yPos(0), VSync(false), EventCallback(nullptr) {}
		};

		WindowData m_Data;
	};

}