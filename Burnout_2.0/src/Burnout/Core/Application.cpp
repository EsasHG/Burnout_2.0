#include "bopch.h"
#include "Application.h"

#include "Burnout/Core/Log.h"

#include "Burnout/Renderer/Renderer.h"

#include "Input.h"

#include "Burnout/Cameras/FirstPersonCameraController.h"
#include "Burnout/Cameras/OrthographicCameraController.h"

#include <GLFW/glfw3.h>

namespace Burnout
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		BO_PROFILE_FUNCTION();
		BO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BO_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}
	
	Application::~Application()
	{
		BO_PROFILE_FUNCTION();
	//	Renderer::Shutdown();	//TODO make
	}

	void Application::PushLayer(Layer* layer)
	{
		BO_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();

	}

	void Application::PushOverlay(Layer* layer)
	{
		BO_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		BO_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BO_BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(BO_BIND_EVENT_FN(Application::OnWindowResized));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		BO_PROFILE_FUNCTION();

		while (m_Running)
		{
			BO_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime(); // should be something like Platform::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					BO_PROFILE_SCOPE("LayerStack OnUpdate");
					for(Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
			}
			m_ImGuiLayer->Begin();
			{
				BO_PROFILE_SCOPE("LayerStack OnImGuiRender");

				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResized(WindowResizeEvent& e)
	{
		BO_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());

		return false;
	}
}
