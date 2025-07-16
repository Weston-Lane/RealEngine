#include "pch.h"
#include "RealApp.h"
#include "Logger.h"

/// <summary>
/// Layer updates happen here
/// </summary>
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
			//UPDATES
			m_window->OnUpdate();
			for (Layer* layer : m_layerStack.GetLayerStack())
				{ layer->OnUpdate(); }
		}
	}
	void RealApp::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(EVENT_FUNC_BIND(OnWindowClose,WindowCloseEvent));

		//PROPOGATING EVENTS INTO THE EVENT LAYERS
		for (auto it = m_layerStack.End() - 1; it != m_layerStack.Begin()-1; --it)//must use -1 at pointers to ensure visitation of all layers
		{
			(*it)->OnEvent(event);
			if(event.m_eventHandled)
				{ break; }
		}
	}
	bool RealApp::OnWindowClose(WindowCloseEvent& e)
	{
		m_isRunning = false;
		return true;
	}

	void RealApp::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
	}
	void RealApp::PopLayer(Layer* layer)
	{
		m_layerStack.PopLayer(layer);
	}
	void RealApp::PushOverlayLayer(Layer* layer)
	{
		m_layerStack.PopOverlayLayer(layer);
	}
	void RealApp::PopOverlayLayer(Layer* layer)
	{
		m_layerStack.PopOverlayLayer(layer);
	}

}
