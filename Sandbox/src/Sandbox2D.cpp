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

	m_VertexArray = Burnout::VertexArray::Create();


	float squareVertices[5 * 4] = {
		-1.f, -1.f, 0.0f, 
		 1.f, -1.f, 0.0f, 
		 1.f,	1.f, 0.0f,
		-1.f,	1.f, 0.0f,
	};


	Burnout::Ref<Burnout::VertexBuffer> squareVB;
	squareVB.reset(Burnout::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

	squareVB->SetLayout({
		{Burnout::ShaderDataType::Float3, "a_Position"},
		});
	m_VertexArray->AddVertexBuffer(squareVB);

	unsigned squareIndices[6] = { 0,1,2,2,3,0 };

	Burnout::Ref<Burnout::IndexBuffer> squareIB;
	squareIB.reset(Burnout::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(squareIB);

	m_FlatColorShader = Burnout::Shader::Create("assets/shaders/FlatColor.glsl");

}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Burnout::Timestep ts)
{
	m_OrthoCamera.OnUpdate(ts);


	Burnout::RenderCommand::SetClearColor({ 0.11f, 0.11f, 0.11f, 1 });
	Burnout::RenderCommand::Clear();

	Burnout::Renderer::BeginScene(m_OrthoCamera.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	
	std::dynamic_pointer_cast<Burnout::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Burnout::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Burnout::Renderer::Submit(m_FlatColorShader, m_VertexArray);

	Burnout::Renderer::EndScene();
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