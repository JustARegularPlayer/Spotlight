#include "splpch.h"
#include "Application.h"
#include "Spotlight/Core/Input.h"

// This has to go... probably later.
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Spotlight
{

	SpotlightApp *SpotlightApp::sm_Instance = nullptr;
	
	SpotlightApp::SpotlightApp()
	{
		SPL_CORE_ASSERT(!sm_Instance, "Application already exists!");
		sm_Instance = this;

		Log::LogInit();

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(SPL_BIND_FUNC(SpotlightApp::OnEvent));

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
		glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
		SPL_INFO("Application size in bytes: {0}", sizeof(SpotlightApp));

		while (m_IsRunning)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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