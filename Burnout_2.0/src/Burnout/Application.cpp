#include "Application.h"
#include "Burnout/Events/ApplicationEvent.h"
#include "Burnout/Log.h"


namespace Burnout
{
	Application::Application()
	{

	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			BO_TRACE(e);
		}

		while (true)
		{
			
		}
	}
}
