#include "RealApp.h"
#include "Logger.h"
#include "Events/ApplicationEvent.h"
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
