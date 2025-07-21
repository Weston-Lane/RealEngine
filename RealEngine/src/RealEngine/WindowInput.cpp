#include "pch.h"
#include "WindowInput.h"
#include "RealApp.h"
#include "GLFW/glfw3.h"

namespace Real
{
    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        auto window = RealApp::Get().GetWindowPtr().GetNativeWindow();
        auto state = glfwGetKey((GLFWwindow*)window, keycode);
        return (state == GLFW_PRESS || state == GLFW_REPEAT);
    }
    bool WindowsInput::IsMouseButtonPressedImpl(int keycode)
    {
        auto window = RealApp::Get().GetWindowPtr().GetNativeWindow();
        auto state = glfwGetMouseButton((GLFWwindow*)window, keycode);
        return (state == GLFW_PRESS || state == GLFW_REPEAT);
        
    }
    std::pair<float, float> WindowsInput::GetMousePosImpl()
    {
        auto window = RealApp::Get().GetWindowPtr().GetNativeWindow();
        double x, y;
        glfwGetCursorPos((GLFWwindow*)window, &x, &y);
        return { (float)x,(float)y };
    }
    float WindowsInput::GetMouseXImpl()
    {   
        return GetMousePosImpl().first;
    }
    float WindowsInput::GetMouseYImpl()
    {
        return GetMousePosImpl().second;
    }
}

