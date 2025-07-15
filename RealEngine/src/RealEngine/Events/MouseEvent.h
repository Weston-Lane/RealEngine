#include "Event.h"
namespace Real
{
	class REAL_EXPORT MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y)
			:m_mouseX(x), m_mouseY(y) {}

		inline float GetX() { return m_mouseX; }
		inline float GetY() { return m_mouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Moved Event: Pos[ " << m_mouseX << " , " << m_mouseY << " ]";
			return ss.str();
		}

		static EventType GetStaticEventType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() const { return GetStaticEventType(); }
		virtual const char* GetName() const { return "Mouse Move"; }

		virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
	private:
		float m_mouseX, m_mouseY;
	};

	class REAL_EXPORT MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float xOffset, float yOffset)
			:m_xOffset(xOffset), m_yOffset(yOffset) {}

		inline float GetXOffset() { return m_xOffset; }
		inline float GetYOffset() { return m_yOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Scrolled Event: Pos[ " << m_xOffset << " , " << m_yOffset << " ]";
			return ss.str();
		}

		static EventType GetStaticEventType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() const { return GetStaticEventType(); }
		virtual const char* GetName() const { return "Mouse Scroll"; }

		virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
	private:
		float m_xOffset, m_yOffset;
	};
	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_button; }
		virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
	protected:
		MouseButtonEvent(int button)
			:m_button(button) {}
		int m_button;
	};
	class REAL_EXPORT MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Pressed Event: [Button:" << m_button << "]";
			return ss.str();
		}

		static EventType GetStaticEventType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() const { return GetStaticEventType(); }
		virtual const char* GetName() const { return "Mouse Button Pressed"; }

	};
	class REAL_EXPORT MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Released Event: [Button:" << m_button << "]";
			return ss.str();
		}

		static EventType GetStaticEventType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() const { return GetStaticEventType(); }
		virtual const char* GetName() const { return "Mouse Button Released"; }

	};
}