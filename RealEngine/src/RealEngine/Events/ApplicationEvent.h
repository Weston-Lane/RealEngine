#pragma once

#include "Event.h"

namespace Real
{
	class REAL_EXPORT WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:m_width(width), m_height(height) {}

		inline unsigned int GetWidth() { return m_width; }
		inline unsigned int GetHeight() { return m_height; }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Resize Event: [Width: " << m_width << " ][Height: " << m_height << " ]";
			return ss.str();
		}

		static EventType GetStaticEventType() { return EventType::WindowResize; }
		virtual EventType GetEventType() const { return GetStaticEventType(); }
		virtual const char* GetName() const { return "Window Resize"; }

		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	private:
		unsigned int m_width, m_height;
	};
	class REAL_EXPORT WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
		
		static EventType GetStaticEventType() { return EventType::WindowClose; }
		virtual EventType GetEventType() const { return GetStaticEventType(); }
		virtual const char* GetName() const { return "Window Close"; }

		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	private:
	};

	//may use later
	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		static EventType GetStaticEventType() { return EventType::AppTick; }
		virtual EventType GetEventType() const { return GetStaticEventType(); }
		virtual const char* GetName() const { return "App Tick"; }

		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		static EventType GetStaticEventType() { return EventType::AppUpdate; }
		virtual EventType GetEventType() const { return GetStaticEventType(); }
		virtual const char* GetName() const { return "App Update"; }

		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		static EventType GetStaticEventType() { return EventType::AppRender; }
		virtual EventType GetEventType() const { return GetStaticEventType(); }
		virtual const char* GetName() const { return "App Render"; }

		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};
}