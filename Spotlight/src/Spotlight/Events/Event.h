#pragma once

#include "splpch.h"
#include "Spotlight/Core/Core.h"

namespace Spotlight
{
	enum class EventType
	{
		None = 0,
		WindowClosed, WindowResized, WindowFocused, WindowLostFocus, WindowMoved,
		CharTyped, KeyPressed, KeyReleased,
		MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased
	};

	enum EventCategory
	{
		EventCategoryApplication	= 1,
		EventCategoryInput			= 1 << 1,
		EventCategoryKeyboard		= 1 << 2,
		EventCategoryMouse			= 1 << 3,
		EventCategoryMouseButton	= 1 << 4
	};

	#define EVENT_CLASS_TYPE(type)	static inline EventType GetStaticType() { return EventType::##type; }					\
									virtual inline EventType GetEventType() const override { return GetStaticType(); }
	
	#define EVENT_CLASS_CATEGORY(category) virtual inline int GetCategoryFlags() const override { return category; }

	// Event system
	class SPOTLIGHT_API Event
	{
	public:
		virtual inline EventType GetEventType() const = 0;
		virtual inline int GetCategoryFlags() const = 0;

		inline bool IsInCategory(int category)
		{
			return GetCategoryFlags() & category;
		}
	public:
		bool IsHandled = false;
	};

	/* Event Dispatcher - Sorts out user-defined functions to certain events.
		Whenever an event is detected, the dispatcher ensures that the function associated to
		the event will always be called.														*/
	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& e)
			: m_Event(e) {}

		template<typename T>
		bool Dispatch(const EventFunc<T>& func)
		{
			SPL_PROFILE_FUNC();

			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.IsHandled = func(*(T*)&m_Event);
				return m_Event.IsHandled;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

}