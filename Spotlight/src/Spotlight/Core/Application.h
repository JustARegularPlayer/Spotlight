#pragma once

#include "Core.h"

#include "Spotlight/Core/Window.h"
#include "Spotlight/Events/Event.h"
#include "Spotlight/Events/AppEvent.h"
#include "Spotlight/Core/LayerStack.h"

#include "Spotlight/ImGui/Layer_ImGui.h"
#include "Spotlight/Core/Timestep.h"
#include "Spotlight/Core/Time.h"

namespace Spotlight
{
	
	class SPOTLIGHT_API SpotlightApp
	{
	public:
		SpotlightApp();
		virtual ~SpotlightApp();

		void OnEvent(Event &e);
		void Run();

		void PushLayer(Layer *layer);
		void PushOverlay(Layer *overlay);

		inline Window &GetWindow() { return *m_Window; }

		static inline SpotlightApp &Get() { return *sm_Instance; }
	private:
		bool OnWindowClose(Event_WindowClosed &e);
	private:
		static SpotlightApp *sm_Instance;

		Scope<Window> m_Window;
		Scope<Time> m_AppTime;
		Layer_ImGui *m_ImGuiLayer;
		bool m_IsRunning = true;

		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	};

	SpotlightApp *CreateApp();

}