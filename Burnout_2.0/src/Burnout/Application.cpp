#include "bopch.h"

#include "Application.h"
#include "Burnout/Events/ApplicationEvent.h"
#include "Burnout/Events/KeyEvent.h"
#include "Burnout/Log.h"

#include <GLFW/glfw3.h>

namespace Burnout
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{


		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
