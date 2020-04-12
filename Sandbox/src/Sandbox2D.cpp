#include "Sandbox2D.h"

#include "imgui/imgui.h"	
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include "Burnout/Cameras/OrthographicCameraController.h"

#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func),  m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
	
		m_Stopped = true;

		float duration = (end - start) * 0.001;

		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name,  [&](ProfileResult profileResult) {m_ProfileResults.push_back(profileResult); });

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_OrthoCamera(1280.f/720.f, true)
{
}
void Sandbox2D::OnAttach()
{
	m_Texture = Burnout::Texture2D::Create("assets/textures/me.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Burnout::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_OrthoCamera.OnUpdate(ts);
	}

	{
		PROFILE_SCOPE("Renderer Prep");

		Burnout::RenderCommand::SetClearColor({ 0.11f, 0.11f, 0.11f, 1 });
		Burnout::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");

		Burnout::Renderer2D::BeginScene(m_OrthoCamera.GetCamera());
	
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		Burnout::Renderer2D::DrawQuad(glm::vec2(-1.f, 0.f), glm::vec2(0.8f, 0.8f), glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
		Burnout::Renderer2D::DrawQuad(glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.75f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f));
		Burnout::Renderer2D::DrawQuad(glm::vec3(0.0f,0.0f, -0.1f), glm::vec2(10.0f,10.0f), m_Texture);
	
		Burnout::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms  ");
		strcat(label, result.Name);

		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Burnout::Event& e)
{
	m_OrthoCamera.OnEvent(e);
}