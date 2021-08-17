#pragma once

#include "Event.h"

namespace Spotlight
{

	class SPOTLIGHT_API Event_WindowClosed : public Event
	{
	public:
		Event_WindowClosed() {}

		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class SPOTLIGHT_API Event_WindowResized : public Event
	{
	public:
		Event_WindowResized(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class SPOTLIGHT_API Event_WindowMoved : public Event
	{
	public:
		Event_WindowMoved(int xPos, int yPos)
			: m_xPos(xPos), m_yPos(yPos) {}

		inline int GetXPos() const { return m_xPos; }
		inline int GetYPos() const { return m_yPos; }

		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		int m_xPos, m_yPos;
	};

}