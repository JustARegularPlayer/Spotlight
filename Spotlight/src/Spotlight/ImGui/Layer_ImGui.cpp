#include "splpch.h"
#include "Layer_ImGui.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Spotlight/Core/Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
		SPL_PROFILE_FUNC();

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void) io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		SpotlightApp& app = SpotlightApp::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Or #version 430 core
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410 core");
	}

	void Layer_ImGui::OnDetach()
	{
		SPL_PROFILE_FUNC();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	
	void Layer_ImGui::Begin()
	{
		SPL_PROFILE_FUNC();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Layer_ImGui::End()
	{
		SPL_PROFILE_FUNC();

		ImGuiIO& io = ImGui::GetIO();
		SpotlightApp& app = SpotlightApp::Get();
		io.DisplaySize = ImVec2((float) app.GetWindow().GetWidth(), (float) app.GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
	}

}