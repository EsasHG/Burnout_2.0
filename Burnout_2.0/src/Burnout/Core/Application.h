#pragma once

#include "Core.h"

#include "Window.h"
#include "Burnout/Core/LayerStack.h"
#include "Burnout/Events/Event.h"
#include "Burnout/Events/ApplicationEvent.h"

#include "Burnout/Core/Timestep.h"

#include "Burnout/ImGui/ImGuiLayer.h"

namespace Burnout
{ 
	class Camera;

	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer = nullptr;
		
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.f;
	private:
		static Application* s_Instance;
	};

	//To be defined in client 
	Application* CreateApplication();
}

