#pragma once

#ifdef BO_PLATFORM_WINDOWS

extern Burnout::Application* Burnout::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Burnout::CreateApplication();
	app->Run();
	delete app;
}
#endif