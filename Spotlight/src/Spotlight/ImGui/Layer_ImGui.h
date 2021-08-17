#pragma once

#include "Spotlight/Core/Layer.h"
#include "Spotlight/Events/AppEvent.h"
#include "Spotlight/Events/KeyEvent.h"
#include "Spotlight/Events/MouseEvent.h"

namespace Spotlight
{

	class SPOTLIGHT_API Layer_ImGui : public Layer
	{
	public:
		Layer_ImGui();
		~Layer_ImGui();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;

		bool OnMouseMoved(Event_MouseMoved& e);
		bool OnMouseScrolled(Event_MouseScrolled& e);
		bool OnMouseButtonPressed(Event_MouseButtonPressed& e);
		bool OnMouseButtonReleased(Event_MouseButtonReleased& e);
		bool OnCharTyped(Event_CharTyped& e);
		bool OnKeyPressed(Event_KeyPressed& e);
		bool OnKeyReleased(Event_KeyReleased& e);
		bool OnWindowResized(Event_WindowResized& e);
	private:
		float m_Time = 0.0f;
	};

}