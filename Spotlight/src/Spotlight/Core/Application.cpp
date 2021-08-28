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

		m_VAO.reset(VertexArray::Create());
		
		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[3] = {0, 1, 2};

		m_IBO.reset(IndexBuffer::Create(indices, std::size(indices)));
		m_Shader.reset(Shader::Create("res/Shaders/Basic.glsl"));

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
			glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VAO->Bind();
			glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr);

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