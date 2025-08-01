#pragma once
#include "RealEngine/PlatformMacros.h"
namespace Real
{
	class REAL_EXPORT Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		static bool IsMouseButtonPressed(int keycode) { return s_Instance->IsMouseButtonPressedImpl(keycode); }
		static std::pair<float,float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int keycode) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}
