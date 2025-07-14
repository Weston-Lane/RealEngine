#pragma once

#ifdef REAL_PLATFORM_WINDOWS

//!Defined in user application
extern Real::RealApp* Real::CreateApp();

int main(int argc, char** argv)
{
	
	auto app = Real::CreateApp();
	RL_CORE_INFO(" Entry Point Contated...");
	app->Run();
	delete app;
}
#endif