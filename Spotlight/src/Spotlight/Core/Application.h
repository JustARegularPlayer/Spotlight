#pragma once

#include "Spotlight/Core/Core.h"
#include "Spotlight/Core/Window.h"
#include "Spotlight/Core/Events/Event.h"
#include "Spotlight/Core/Events/AppEvent.h"
#include "Spotlight/Core/LayerStack.h"

namespace Spotlight
{
	
	class SPOTLIGHT_API SpotlightApp
	{
	public:
		SpotlightApp();
		virtual ~SpotlightApp();

		void OnEvent(Event& e);
		void Run();

		inline Window& GetWindow() { return *m_Window; }

		static inline SpotlightApp& Get() { return *sm_Instance; }
	private:
		bool OnWindowClose(Event_WindowClosed& e);

		static SpotlightApp* sm_Instance;

		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;

		LayerStack m_LayerStack;
	};

	SpotlightApp* CreateApp();

}