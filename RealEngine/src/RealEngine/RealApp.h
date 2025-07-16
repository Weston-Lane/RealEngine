#pragma once
#include "PlatformMacros.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
namespace Real
{
	class REAL_EXPORT RealApp
	{
	public:
		bool m_isRunning = true;
		RealApp();
		virtual ~RealApp();
		void Run();
		void OnEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_window;
		
	};
	
	//Defined in user application
	RealApp* CreateApp();
}