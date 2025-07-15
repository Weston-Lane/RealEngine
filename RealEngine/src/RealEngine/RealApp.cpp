#include "pch.h"
#include "RealApp.h"
#include "Logger.h"
#include "Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"
namespace Real
{
	RealApp::RealApp()
	{

	}
	RealApp::~RealApp()
	{

	}
	void RealApp::Run()
	{
		RL_CORE_DEBUG("EVENT SYSTEM CHECK:")
		WindowCloseEvent event;
		RL_CORE_TRACE(" {}",event.ToString());
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>
		(
				[](WindowCloseEvent& e)
				{
					RL_CORE_INFO(" Handled WindowCloseEvent");
					return true;
				}
		);

		while (true);
	}
}
