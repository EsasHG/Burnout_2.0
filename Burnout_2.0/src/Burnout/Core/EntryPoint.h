#pragma once

#ifdef BO_PLATFORM_WINDOWS

extern Burnout::Application* Burnout::CreateApplication();

int main(int argc, char** argv)
{
	Burnout::Log::Init();
	BO_CORE_WARN("Initialized Log!");
	int a = 5;
	BO_TRACE("Hello! Var={0}", a);

	auto app = Burnout::CreateApplication();
	app->Run();
	delete app;
}
#endif