#pragma once
#ifdef REAL_PLATFORM_WINDOWS

//!Defined in application
extern Real::RealApp* Real::CreateApp();

int main(int argc, char** argv)
{
	
	auto app = Real::CreateApp();
	std::println("Entry Point Contacted");
	app->Run();
	delete app;
}
#endif