#include "pch.h"
#include "RealApp.h"
#include "Logger.h"
#include "GLFW/glfw3.h"
#include "RealEngine/WindowInput.h"
//#include "backends/imgui_impl_glfw.h"
//#include "backends/imgui_impl_opengl3.h"


/// <summary>
/// Layer updates happen here
/// </summary>
namespace Real
{
	#define EVENT_FUNC_BIND(func,type) [&](Event& event) { return func(static_cast<type&>(event)); }//std::bind(&RealApp::OnEvent, this, std::placeholders::_1);

	REAL_EXPORT RealApp* RealApp::s_Instance = nullptr;

	RealApp::RealApp()
	{
		//application singleton
		REAL_ASSERT(s_Instance==nullptr, "RealApp Singleton alredy Created!");
		s_Instance = this;

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
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_layerStack.GetLayerStack())
				{ layer->OnUpdate(); }

			m_window->OnUpdate();
		}
	}
	void RealApp::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(EVENT_FUNC_BIND(OnWindowClose,WindowCloseEvent));

		//PROPOGATING EVENTS INTO THE LAYERS
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
		m_layerStack.PushOverlayLayer(layer);
	}
	void RealApp::PopOverlayLayer(Layer* layer)
	{
		m_layerStack.PopOverlayLayer(layer);
	}

}
