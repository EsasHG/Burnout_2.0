#include "Sandbox2D.h"

#include "imgui/imgui.h"	
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Burnout/Cameras/OrthographicCameraController.h"
Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_OrthoCamera(1280.f/720.f, true)
{
}
void Sandbox2D::OnAttach()
{


}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Burnout::Timestep ts)
{
	m_OrthoCamera.OnUpdate(ts);


	Burnout::RenderCommand::SetClearColor({ 0.11f, 0.11f, 0.11f, 1 });
	Burnout::RenderCommand::Clear();

	Burnout::Renderer2D::BeginScene(m_OrthoCamera.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	
	Burnout::Renderer2D::DrawQuad(glm::vec2(0.f,0.f ), glm::vec2(1.f,1.f ), glm::vec4(0.8f, 0.2f,0.3f,1.0f));

	Burnout::Renderer2D::EndScene();
	
	//TODO add these functions:
	//std::dynamic_pointer_cast<Burnout::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<Burnout::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Burnout::Event& e)
{
	m_OrthoCamera.OnEvent(e);
}