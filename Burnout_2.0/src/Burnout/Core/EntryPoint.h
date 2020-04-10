#pragma once

#ifdef BO_PLATFORM_WINDOWS

extern Burnout::Application* Burnout::CreateApplication();

int main(int argc, char** argv)
{
	Burnout::Log::Init();
	BO_CORE_WARN("Initialized Log!");

	auto app = Burnout::CreateApplication();
	app->Run();
	delete app;
}
#endif