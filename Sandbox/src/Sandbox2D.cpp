#include "Sandbox2D.h"

#include "imgui/imgui.h"	
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include "Burnout/Cameras/OrthographicCameraController.h"


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_OrthoCamera(1280.f/720.f, true)
{
}
void Sandbox2D::OnAttach()
{
	BO_PROFILE_FUNCTION();

	m_Texture = Burnout::Texture2D::Create("assets/textures/me.png");
}

void Sandbox2D::OnDetach()
{
	BO_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Burnout::Timestep ts)
{
	BO_PROFILE_FUNCTION();

	m_OrthoCamera.OnUpdate(ts);

	{
		BO_PROFILE_SCOPE("Renderer Prep");

		Burnout::RenderCommand::SetClearColor({ 0.11f, 0.11f, 0.11f, 1 });
		Burnout::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 20.f;
		BO_PROFILE_SCOPE("Renderer Draw");

		Burnout::Renderer2D::BeginScene(m_OrthoCamera.GetCamera());
	
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		Burnout::Renderer2D::DrawQuad(glm::vec3(0.5f, -0.5f, 0.f), glm::vec2(0.5f, 0.75f), glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
		Burnout::Renderer2D::DrawQuad(glm::vec3(-1.f, 0.f, 0.f), glm::vec2(0.8f, 0.8f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f));
		Burnout::Renderer2D::DrawRotatedQuad(glm::vec3(1.f, 0.f, 1.f), glm::vec2(0.8f, 0.8f),-45.f, glm::vec4(0.2f, 0.8f, 0.2f, 1.0f));
		Burnout::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.1f), glm::vec2(100.0f, 100.0f), m_Texture, 1.f);
		Burnout::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.1f), glm::vec2(1.0f, 1.0f), m_Texture, 1.f);
		Burnout::Renderer2D::DrawRotatedQuad(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), rotation, m_Texture, 1.f);
	
		//Burnout::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Burnout::Renderer2D::DrawQuad(glm::vec2(-1.0f, 0.0f), glm::vec2(0.8f, 0.8f  ), glm::vec4( 0.8f, 0.2f, 0.3f, 1.0f ));
		Burnout::Renderer2D::DrawQuad(glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.75f ), glm::vec4( 0.2f, 0.3f, 0.8f, 1.0f ));
		Burnout::Renderer2D::DrawQuad(glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.75f ), glm::vec4( 0.2f, 0.3f, 0.8f, 1.0f ));
		//Burnout::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, 10.0f);

		Burnout::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{

	BO_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Burnout::Event& e)
{
	m_OrthoCamera.OnEvent(e);
}