#pragma once
#include "RealEngine/Input.h"

namespace Real
{
	class WindowsInput : public Input
	{
	protected:

		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int keycode) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

	private:
	};
}