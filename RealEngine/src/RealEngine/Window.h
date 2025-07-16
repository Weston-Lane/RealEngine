#pragma once
#include "pch.h"
#include "PlatformMacros.h"
#include "Events/Event.h"

/// <summary>
/// Window class interface for platform specific windows
/// </summary>
namespace Real
{
	struct WindowProps
	{
		std::string m_title;
		uint32_t m_width, m_height;

		WindowProps(std::string title = "Real Engine", uint32_t width = 1280, uint32_t height = 720) // loads default val if no args
			:m_title(title), m_width(width), m_height(height) {}
	};

	 class Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void SetEventCallBack(const EventCallbackFunc&) = 0;
		virtual void SetVsync(bool set) = 0;
		virtual bool IsVsyncOn() const = 0;
		
		static std::unique_ptr<Window> Create(WindowProps props = WindowProps());
	};
}
