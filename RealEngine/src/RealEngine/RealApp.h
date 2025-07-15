#pragma once
#include "PlatformMacros.h"
namespace Real
{
	class REAL_EXPORT RealApp
	{
	public:
		RealApp();
		virtual ~RealApp();
		void Run();
	private:
	};

	//Defined in user application
	RealApp* CreateApp();
}