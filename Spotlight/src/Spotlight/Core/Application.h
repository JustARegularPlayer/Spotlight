#pragma once

#include "Spotlight/Core/Core.h"
#include "Spotlight/Core/Window.h"
#include "Spotlight/Events/Event.h"
#include "Spotlight/Events/AppEvent.h"
#include "Spotlight/Core/LayerStack.h"

#include "Spotlight/Renderer/Buffer.h"
#include "Spotlight/Renderer/Shader.h"

#include "Spotlight/ImGui/Layer_ImGui.h"

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

		static SpotlightApp *sm_Instance;

		std::unique_ptr<Window> m_Window;
		Layer_ImGui *m_ImGuiLayer;
		bool m_IsRunning = true;

		LayerStack m_LayerStack;

		unsigned int m_VAO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
	};

	SpotlightApp *CreateApp();

}