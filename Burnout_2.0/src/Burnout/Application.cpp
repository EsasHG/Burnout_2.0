#include "Application.h"
#include "Burnout/Events/ApplicationEvent.h"
#include "Burnout/Events/KeyEvent.h"
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
		KeyPressedEvent k(14, 0);
		if (e.IsInCategory(EventCategoryApplication))
		{
			BO_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			BO_TRACE(e);
		}
		if (k.GetStaticType() == EventType::KeyPressed)
		{
			BO_TRACE(k);
		}
		if (k.GetStaticType() == EventType::KeyReleased)
		{
			BO_ERROR(k);
		}

		while (true)
		{
			
		}
	}
}
