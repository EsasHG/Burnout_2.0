#include <Burnout.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "imgui/imgui.h"

class ExampleLayer : public Burnout::ImGuiLayer
{
public:
	ExampleLayer()
		:ImGuiLayer()
	{
	}

	void OnUpdate() override
	{
		if (Burnout::Input::IsKeyPressed(BO_KEY_TAB))
			BO_INFO("Tab key is pressed!");
		
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello piss!");
		ImGui::End();
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
	}
	~Sandbox()
	{

	}

};
Burnout::Application* Burnout::CreateApplication()
{
	return new Sandbox();
}