#pragma once

#include "RealEngine/Layer.h"
#include "RealEngine/Events/Event.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "RealEngine/RealApp.h"

namespace Real
{
	class REAL_EXPORT ImGuiLayer : public Layer
	{
	public:
		
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
		
	private:
		GLFWwindow* m_window;
		RealApp& m_app = RealApp::Get();
		ImGuiIO* m_io;
	};
}
