#include "splpch.h"
#include "Application.h"

#include "Spotlight/Renderer/Renderer.h"

namespace Spotlight
{

	SpotlightApp *SpotlightApp::sm_Instance = nullptr;
	
	SpotlightApp::SpotlightApp()
	{
		SPL_PROFILE_FUNC();

		SPL_CORE_ASSERT(!sm_Instance, "Application already exists!");
		sm_Instance = this;

		Log::LogInit();
		
		m_Window = Window::Create();
		m_Window->SetEventCallback(SPL_BIND_FUNC(SpotlightApp::OnEvent));

		m_AppTime = Time::Create();

		Renderer::Init();

		m_ImGuiLayer = new Layer_ImGui();
		PushOverlay(m_ImGuiLayer);
	}

	SpotlightApp::~SpotlightApp()
	{
		PopOverlay(m_ImGuiLayer);
	}

	void SpotlightApp::OnEvent(Event& e)
	{
		SPL_PROFILE_FUNC();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Event_WindowClosed>(SPL_BIND_FUNC(SpotlightApp::OnWindowClose));
		dispatcher.Dispatch<Event_WindowResized>(SPL_BIND_FUNC(SpotlightApp::OnWindowResized));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			SPL_PROFILE_SCOPE("SpotlightApp::OnEvent() Loop");
			(*--it)->OnEvent(e);
			if (e.IsHandled)
				break;
		}
	}

	void SpotlightApp::Run()
	{
		SPL_PROFILE_FUNC();

		while (m_IsRunning)
		{
			SPL_PROFILE_SCOPE("Render Frame - SpotlightApp::Run()");

			m_AppTime->UpdateTime();
			Timestep timestep = m_AppTime->GetTime() - m_LastFrameTime;
			m_LastFrameTime = m_AppTime->GetTime();

			if (!m_Minimized)
			{
				SPL_PROFILE_SCOPE("Layer OnUpdate()");
				for (Layer *layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			{
				SPL_PROFILE_SCOPE("Layer OnUIRender()");
				m_ImGuiLayer->Begin();
				for (Layer *layer : m_LayerStack)
					layer->OnUIRender();
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	void SpotlightApp::PushLayer(Layer* layer)
	{
		SPL_PROFILE_FUNC();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void SpotlightApp::PushOverlay(Layer* overlay)
	{
		SPL_PROFILE_FUNC();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void SpotlightApp::PopLayer(Layer *layer)
	{
		SPL_PROFILE_FUNC();

		layer->OnDetach();
		m_LayerStack.PopLayer(layer);
	}

	void SpotlightApp::PopOverlay(Layer *overlay)
	{
		SPL_PROFILE_FUNC();

		overlay->OnDetach();
		m_LayerStack.PopOverlay(overlay);
	}

	bool SpotlightApp::OnWindowClose(Event_WindowClosed &e)
	{
		m_IsRunning = false;
		return true;
	}

	bool SpotlightApp::OnWindowResized(Event_WindowResized &e)
	{
		SPL_PROFILE_FUNC();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());
		return false;
	}

}