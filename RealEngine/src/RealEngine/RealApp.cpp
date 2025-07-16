#include "pch.h"
#include "RealApp.h"
#include "Logger.h"
#include "GLFW/glfw3.h"
namespace Real
{
#define EVENT_FUNC_BIND(func,type) [&](Event& event) { return func(static_cast<type&>(event)); }//std::bind(&RealApp::OnEvent, this, std::placeholders::_1);
	RealApp::RealApp()
	{
		m_window = Window::Create();
		std::function<void(Event&)> callback = [&](Event& event) { return OnEvent(event); }; 
		m_window->SetEventCallBack(callback);
	}
	RealApp::~RealApp()
	{

	}
	void RealApp::Run()
	{
		while (m_isRunning)
		{
			glClearColor(.5, .5, .5, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			m_window->OnUpdate();
		}
	}
	void RealApp::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(EVENT_FUNC_BIND(OnWindowClose,WindowCloseEvent));
		RL_CORE_TRACE("{}",event.ToString());
	}
	bool RealApp::OnWindowClose(WindowCloseEvent& e)
	{
		m_isRunning = false;
		return true;
	}

}
