#pragma once
#include "PlatformMacros.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
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
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlayLayer(Layer* layer);
		void PopOverlayLayer(Layer* layer);
		
	private:
		std::unique_ptr<Window> m_window;
		LayerStack m_layerStack;
		
	};
	
	//Defined in user application
	RealApp* CreateApp();
}