#include <Burnout.h>

class ExampleLayer : public Burnout::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Burnout::Input::IsKeyPressed(BO_KEY_TAB))
			BO_INFO("Tab key is pressed!");
	
	}

	void OnEvent(Burnout::Event& event) override
	{
	}

};

class Sandbox : public Burnout::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Burnout::ImGuiLayer());
	}
	~Sandbox()
	{

	}

};
Burnout::Application* Burnout::CreateApplication()
{
	return new Sandbox();
}