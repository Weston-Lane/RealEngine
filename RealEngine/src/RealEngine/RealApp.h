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
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlayLayer(Layer* layer);
		void PopOverlayLayer(Layer* layer);

		void OnEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& e);

		inline static RealApp& Get() { return *s_Instance; }
		inline Window& GetWindowPtr() { return *m_window; }

	private:
		std::unique_ptr<Window> m_window;
		LayerStack m_layerStack;
		static RealApp* s_Instance;
		
	};
	
	//Defined in user application
	RealApp* CreateApp();
}