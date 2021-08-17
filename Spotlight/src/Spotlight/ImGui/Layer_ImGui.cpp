#include "splpch.h"
#include "Layer_ImGui.h"

#include <imgui.h>
#include "Spotlight/Core/Application.h"
#include "Spotlight/Core/KeyCodes.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

// Delete this/these include(s) at some time
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Spotlight
{

	Layer_ImGui::Layer_ImGui()
	{
	}

	Layer_ImGui::~Layer_ImGui()
	{
	}

	void Layer_ImGui::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = SPL_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = SPL_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SPL_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SPL_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SPL_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = SPL_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = SPL_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = SPL_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = SPL_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = SPL_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = SPL_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SPL_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = SPL_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = SPL_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = SPL_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = SPL_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = SPL_KEY_A;
		io.KeyMap[ImGuiKey_C] = SPL_KEY_C;
		io.KeyMap[ImGuiKey_V] = SPL_KEY_V;
		io.KeyMap[ImGuiKey_X] = SPL_KEY_X;
		io.KeyMap[ImGuiKey_Y] = SPL_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = SPL_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410 core");
		// Or #version 430 core
	}

	void Layer_ImGui::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
	}
	
	void Layer_ImGui::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		SpotlightApp& app = SpotlightApp::Get();
		io.DisplaySize = ImVec2((float) app.GetWindow().GetWidth(), (float) app.GetWindow().GetHeight());

		float time = (float) glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool showDemo = true;
		ImGui::ShowDemoWindow(&showDemo);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Layer_ImGui::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Event_MouseMoved>(SPL_BIND_FUNC(Layer_ImGui::OnMouseMoved));
		dispatcher.Dispatch<Event_MouseScrolled>(SPL_BIND_FUNC(Layer_ImGui::OnMouseScrolled));
		dispatcher.Dispatch<Event_MouseButtonPressed>(SPL_BIND_FUNC(Layer_ImGui::OnMouseButtonPressed));
		dispatcher.Dispatch<Event_MouseButtonReleased>(SPL_BIND_FUNC(Layer_ImGui::OnMouseButtonReleased));
		dispatcher.Dispatch<Event_CharTyped>(SPL_BIND_FUNC(Layer_ImGui::OnCharTyped));
		dispatcher.Dispatch<Event_KeyPressed>(SPL_BIND_FUNC(Layer_ImGui::OnKeyPressed));
		dispatcher.Dispatch<Event_KeyReleased>(SPL_BIND_FUNC(Layer_ImGui::OnKeyReleased));
		dispatcher.Dispatch<Event_WindowResized>(SPL_BIND_FUNC(Layer_ImGui::OnWindowResized));
	}

	bool Layer_ImGui::OnMouseMoved(Event_MouseMoved& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetXPos(), e.GetYPos());
		return false;
	}

	bool Layer_ImGui::OnMouseScrolled(Event_MouseScrolled& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
		return false;
	}

	bool Layer_ImGui::OnMouseButtonPressed(Event_MouseButtonPressed& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetButton()] = true;
		return false;
	}

	bool Layer_ImGui::OnMouseButtonReleased(Event_MouseButtonReleased& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetButton()] = false;
		return false;
	}

	bool Layer_ImGui::OnCharTyped(Event_CharTyped& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if(keycode > 0 && keycode <= 0x10000)
			io.AddInputCharacter((unsigned short) keycode);
		return false;
	}

	bool Layer_ImGui::OnKeyPressed(Event_KeyPressed& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[SPL_KEY_LEFT_CONTROL] || io.KeysDown[SPL_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[SPL_KEY_LEFT_SHIFT] || io.KeysDown[SPL_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[SPL_KEY_LEFT_ALT] || io.KeysDown[SPL_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[SPL_KEY_LEFT_SUPER] || io.KeysDown[SPL_KEY_RIGHT_SUPER];

		return false;
	}

	bool Layer_ImGui::OnKeyReleased(Event_KeyReleased& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}

	bool Layer_ImGui::OnWindowResized(Event_WindowResized& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float) e.GetWidth(), (float) e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(1, 1, e.GetWidth(), e.GetHeight());
		return false;
	}

}