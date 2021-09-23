#pragma once

#include "Event.h"

namespace Spotlight
{

	class SPOTLIGHT_API BaseEvent_Key : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	protected:
		BaseEvent_Key(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class SPOTLIGHT_API Event_KeyPressed : public BaseEvent_Key
	{
	public:
		Event_KeyPressed(int keycode, int repeatCount)
			: BaseEvent_Key(keycode), m_RepeatCount(repeatCount) {}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class SPOTLIGHT_API Event_KeyReleased : public BaseEvent_Key
	{
	public:
		Event_KeyReleased(int keycode)
			: BaseEvent_Key(keycode) {}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class SPOTLIGHT_API Event_CharTyped : public BaseEvent_Key
	{
	public:
		Event_CharTyped(int keycode)
			: BaseEvent_Key(keycode) {}

		EVENT_CLASS_TYPE(CharTyped)
	};

}