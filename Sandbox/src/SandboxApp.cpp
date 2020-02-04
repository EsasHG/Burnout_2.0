#include "bopch.h"
#include "Burnout.h"

class Sandbox : public Burnout::Application
{
public: 
	Sandbox()
	{

	}
	~Sandbox()
	{

	}

};
Burnout::Application* Burnout::CreateApplication()
{
	return new Sandbox();
}