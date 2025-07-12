#pragma once
#include "platform/PlatformMacros.h"
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

	//Defined in application
	RealApp* CreateApp();
}