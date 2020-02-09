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
		//BO_INFO("ExampleLayer::Update");
	}

	void OnEvent(Burnout::Event& event) override
	{
		//BO_TRACE("{0}", event);
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