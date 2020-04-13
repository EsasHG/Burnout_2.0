#pragma once

#ifdef BO_PLATFORM_WINDOWS

extern Burnout::Application* Burnout::CreateApplication();

int main(int argc, char** argv)
{
	Burnout::Log::Init();
	BO_PROFILE_BEGIN_SESSION("Startup", "BurnoutProfile-Startup.json");
	auto app = Burnout::CreateApplication();
	BO_PROFILE_END_SESSION();
	BO_PROFILE_BEGIN_SESSION("Runtime", "BurnoutProfile-Runtime.json");
	app->Run();
	BO_PROFILE_END_SESSION();
	BO_PROFILE_BEGIN_SESSION("Shutdown", "BurnoutProfile-Shutdown.json");
	delete app;
	BO_PROFILE_END_SESSION();

}
#endif