#pragma once
#include "Core.h"
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

