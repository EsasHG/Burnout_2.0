#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Burnout
{

	class BURNOUT_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//To be defined in client 
	Application* CreateApplication();
}

