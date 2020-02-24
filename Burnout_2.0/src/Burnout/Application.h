#pragma once

#include "Core.h"

#include "Window.h"
#include "Burnout/LayerStack.h"
#include "Events/Event.h"
#include "Burnout/Events/ApplicationEvent.h"

#include "Burnout/ImGui/ImGuiLayer.h"

#include "Burnout/Renderer/Shader.h"
#include "Burnout/Renderer/Buffer.h"
#include "Burnout/Renderer/VertexArray.h"


namespace Burnout
{ 

	class BURNOUT_API Application
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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer = nullptr;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static Application* s_Instance;
	};

	//To be defined in client 
	Application* CreateApplication();
}

