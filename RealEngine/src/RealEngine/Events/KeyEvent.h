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
		KeyPressedEvent(int keyCode, int repeatCount, int mods)
			:KeyEvent(keyCode), m_repeatCount(repeatCount), m_mods(mods) {}

		int IsRepeat() const { return m_repeatCount; }
		int GetMods() const { return m_mods; }
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
		int m_mods;
	};

	class REAL_EXPORT KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode, int mods)
			:KeyEvent(keycode), m_mods(mods) {}

		int GetMods() const { return m_mods; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Pressed [Key: " << m_keyCode << "]";
			return ss.str();
		}
		
		static EventType GetStaticEventType() { return EventType::KeyReleased; }//static is needed for function like dispatcher since it does not need the specific instance data of the class
		virtual EventType GetEventType() const override { return GetStaticEventType(); }
		virtual const char* GetName() const override { return "Key Released"; }
	private:
		int m_mods;
	};

	class REAL_EXPORT KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int uniCodeChar)
			:KeyEvent(uniCodeChar), character(uniCodeChar){}

		char GetChar() { return character; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Typed [Key: " << m_keyCode << "]";
			return ss.str();
		}

		static EventType GetStaticEventType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override { return GetStaticEventType(); }
		virtual const char* GetName() const override { return "Key Typed"; }
	private:
		char character;
	};
}
