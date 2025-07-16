#pragma once
#include "Event.h"

namespace Real
{
	class REAL_EXPORT KeyEvent : public Event
	{
	public:
		static enum State
		{
			Pressed, Held
		};
		int GetKeyCode() const { return m_keyCode; }
		virtual int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; } //KeyEvent is both a keyboard and input event
	protected:
		KeyEvent(int keycode) //constructor can only be called by child
			: m_keyCode(keycode) {}
		int m_keyCode;
	private:
	};

	class REAL_EXPORT KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			:KeyEvent(keyCode), m_repeatCount(repeatCount) {}

		int IsRepeat() const { return m_repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Pressed [Key: " << m_keyCode << "]" << "(Repeats: " << m_repeatCount << ")";
			return ss.str();
		}

		static EventType GetStaticEventType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override { return GetStaticEventType(); }
		virtual const char* GetName() const override { return "Key Pressed"; }
		
	private:
		int m_repeatCount;
	};

	class REAL_EXPORT KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Pressed [Key: " << m_keyCode << "]";
			return ss.str();
		}
		
		static EventType GetStaticEventType() { return EventType::KeyReleased; }//static is needed for function like dispatcher since it does not need the specific instance data of the class
		virtual EventType GetEventType() const override { return GetStaticEventType(); }
		virtual const char* GetName() const override { return "Key Released"; }
	};
}
