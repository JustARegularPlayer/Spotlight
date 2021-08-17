#pragma once

#include "Event.h"

namespace Spotlight
{

	class SPOTLIGHT_API Event_MouseMoved : public Event
	{
	public:
		Event_MouseMoved(float xPos, float yPos)
			: m_xPos(xPos), m_yPos(yPos) {}

		inline float GetXPos() const { return m_xPos; }
		inline float GetYPos() const { return m_yPos; }

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_xPos, m_yPos;
	};
	
	class SPOTLIGHT_API Event_MouseScrolled : public Event
	{
	public:
		Event_MouseScrolled(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset) {}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_xOffset, m_yOffset;
	};

	class SPOTLIGHT_API BaseEvent_MouseButton : public Event
	{
	public:
		inline int GetButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	protected:
		BaseEvent_MouseButton(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class SPOTLIGHT_API Event_MouseButtonPressed : public BaseEvent_MouseButton
	{
	public:
		Event_MouseButtonPressed(int button)
			: BaseEvent_MouseButton(button) {}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class SPOTLIGHT_API Event_MouseButtonReleased : public BaseEvent_MouseButton
	{
	public:
		Event_MouseButtonReleased(int button)
			: BaseEvent_MouseButton(button) {}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}