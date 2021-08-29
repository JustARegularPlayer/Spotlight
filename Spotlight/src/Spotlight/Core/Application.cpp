#include "splpch.h"
#include "Application.h"
#include "Spotlight/Core/Input.h"

// Temporary header includes
#include <glad/glad.h>

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

		float vertices[7 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		uint32_t indices[3 * 2] = 
		{
			0, 1, 2,
			2, 3, 0
		};

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "i_Position", false},
				{ShaderDataType::Float4, "i_Color", false},
			};

			m_VBO->SetLayout(layout);
		}

		uint32_t i = 0;
		const auto &layout = m_VBO->GetLayout();
		for (const auto &element : layout)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i,
				element.GetComponentCount(),
				GL_FLOAT,
				element.Normalized,
				layout.GetStride(),
				(const void *) element.Offset);
			i++;
		}

		m_IBO.reset(IndexBuffer::Create(indices, (uint32_t)std::size(indices)));
		m_Shader.reset(Shader::Create("assets/Shaders/Basic.glsl"));
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

			glBindVertexArray(m_VAO);
			m_Shader->Bind();
			m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
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
		glDeleteVertexArrays(1, &m_VAO);
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