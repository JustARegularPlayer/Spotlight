#include "splpch.h"
#include "Application.h"

#include "Spotlight/Renderer/Renderer.h"

namespace Spotlight
{

	SpotlightApp *SpotlightApp::sm_Instance = nullptr;
	
	SpotlightApp::SpotlightApp()
	{
		SPL_CORE_ASSERT(!sm_Instance, "Application already exists!");
		sm_Instance = this;

		Log::LogInit();
		
		m_Window = Window::Create();
		m_Window->SetEventCallback(SPL_BIND_FUNC(SpotlightApp::OnEvent));

		m_AppTime = Time::Create();

		m_ImGuiLayer = new Layer_ImGui();
		PushOverlay(m_ImGuiLayer);
	}

	SpotlightApp::~SpotlightApp()
	{
	}

	void SpotlightApp::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Event_WindowClosed>(SPL_BIND_FUNC(SpotlightApp::OnWindowClose));
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled)
				break;
		}
	}

	void SpotlightApp::Run()
	{
		while (m_IsRunning)
		{
			m_AppTime->UpdateTime();
			Timestep timestep = m_AppTime->GetTime() - m_LastFrameTime;
			m_LastFrameTime = m_AppTime->GetTime();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUIRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void SpotlightApp::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void SpotlightApp::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool SpotlightApp::OnWindowClose(Event_WindowClosed &e)
	{
		m_IsRunning = false;
		return true;
	}

}