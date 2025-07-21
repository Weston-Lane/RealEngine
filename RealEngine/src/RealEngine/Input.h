#pragma once

namespace Real
{
	class REAL_EXPORT Input
	{
	public:
		static bool IsKeyPressed(int keycode) {}
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		
	private:
		static Input* s_Instance;
	};
}
