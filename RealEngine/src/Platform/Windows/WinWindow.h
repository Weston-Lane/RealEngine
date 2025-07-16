#pragma once
#include "pch.h"
#include "GLFW/glfw3.h"
#include "RealEngine/Window.h"

namespace Real
{
	class WinWindow : public Window
	{
	public:
		WinWindow(const WindowProps& props);
		~WinWindow();
		
		virtual void OnUpdate() override;
		inline virtual uint32_t GetWidth() const override { return m_data.width; }
		inline virtual uint32_t GetHeight() const override { return m_data.height; };
		virtual void SetEventCallBack(const EventCallbackFunc&) override;
		virtual void SetVsync(bool set) override;
		virtual bool IsVsyncOn() const override;
	private:
		void Init(const WindowProps& props);
		void ShutDown();

		GLFWwindow* m_window;
		struct WindowData
		{
			std::string title;
			uint32_t width, height;
			bool VsyncOn;
			EventCallbackFunc EventCallback;
		};
		WindowData m_data; // will be used to pass into GLFW the to application without direct interaction of window and app
	};

}