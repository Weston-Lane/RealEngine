#include <glad/glad.h>
#include "WinWindow.h"
#include "RealEngine/Logger.h"
#include "RealEngine/Events/ApplicationEvent.h"
#include "RealEngine/Events/KeyEvent.h"
#include "RealEngine/Events/MouseEvent.h"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
/// <summary>
/// GLFW and WinWindow initialization
/// Later iterations will use winAPI
/// </summary>
namespace Real
{
	static bool glfwIsInit = false;
	static void glfwErrorCallback(int error_code, const char* description)
	{
		RL_CORE_ERROR("GLFW error code[{0}]: {1}", error_code, description);
	}
	std::unique_ptr<Window> Window::Create(WindowProps props)
	{
		#ifdef REAL_PLATFORM_WINDOWS
				return std::make_unique<WinWindow>(props);
		#endif
	}

	WinWindow::WinWindow(const WindowProps& props)
	{
		Init(props);
	}
	WinWindow::~WinWindow()
	{
		ShutDown();
	}
	void WinWindow::Init(const WindowProps& props)
	{
		m_data.title = props.m_title;
		m_data.width = props.m_width;
		m_data.height = props.m_height;

		/////////////////Init Glfw////////////////////////////////////
		if(!glfwIsInit)
		{
			bool success = glfwInit();
			REAL_CORE_ASSERT(success, "glfw could not initialize!");
			glfwIsInit = true;
			glfwSetErrorCallback(glfwErrorCallback);
		}
		else 
			{ RL_CORE_INFO(" glfw already initialized...."); }

		m_window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		/////////////////Init Glad////////////////////////////////////
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		REAL_CORE_ASSERT(success, "glad could not load OpenGL function pointers!");
		/////////////////Init Glad////////////////////////////////////
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVsync(true);

		//set GLFW callbacks// Could possibly move into own function. Would just need to change the private access modifier
		glfwSetWindowSizeCallback(m_window, 
		[](GLFWwindow* window, int width, int height)
		{
			//load data from windowUserPointer. taking the reference to change the data for the window object created earlier
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);

		});
		glfwSetWindowCloseCallback(m_window, 
		[](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
		glfwSetKeyCallback(m_window, 
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, KeyEvent::State::Pressed,mods);
						data.EventCallback(event);
					}break;
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key,mods);
						data.EventCallback(event);
					}break;
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, KeyEvent::State::Held, mods);//WINAPI can give a repeat count GLFW does not so set to 1
						data.EventCallback(event);
					}break;
				}
				RL_DEBUG("Key {0} Action {1}\n", key, action);
		});
		glfwSetMouseButtonCallback(m_window,
		[](GLFWwindow* window, int button, int action, int mods)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
					}break;
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
					}break;
				}
		});
		glfwSetScrollCallback(m_window,
		[](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent event((float)xOffset,(float)yOffset);
			data.EventCallback(event);

		});
		glfwSetCursorPosCallback(m_window,
		[](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
		glfwSetWindowPosCallback(m_window,
		[](GLFWwindow* window, int xpos, int ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowMoveEvent event(xpos, ypos);
			data.EventCallback(event);
		});
		glfwSetCharCallback(m_window,
		[](GLFWwindow* window, unsigned int unicodeChar)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(unicodeChar);
			data.EventCallback(event);
		});

	}
	void WinWindow::ShutDown()
	{
		glfwDestroyWindow(m_window);
	}
	void WinWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);		
	}
	void WinWindow::SetEventCallBack(const EventCallbackFunc& eventFunc)
	{
		m_data.EventCallback = eventFunc;
	}
	void WinWindow::SetVsync(bool set)
	{
		if(set)
			{ glfwSwapInterval(1); }
		else
			{ glfwSwapInterval(0); }

		m_data.VsyncOn = set;
	}
	bool WinWindow::IsVsyncOn() const
	{
		return m_data.VsyncOn;
	}

}