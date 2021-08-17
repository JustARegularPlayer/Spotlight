#pragma once

#include "splpch.h"
#include "Spotlight/Core/Core.h"
#include "Spotlight/Events/Event.h"

namespace Spotlight
{

	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(std::string title = "Spotlight Engine", unsigned int width = 1067, unsigned int height = 600)
			: Title(title), Width(width), Height(height) {}
	};

	class SPOTLIGHT_API Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual inline unsigned int GetWidth() const = 0;
		virtual inline unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunc& func) = 0;
		virtual void SetVSync(bool isEnabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());
	};

}