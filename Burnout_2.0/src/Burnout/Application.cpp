#include "bopch.h"

#include "Application.h"
#include "Burnout/Events/KeyEvent.h"
#include "Burnout/Log.h"
#include "Input.h"
#include "Burnout/Renderer/Shader.h"

#include <glad/glad.h>

namespace Burnout
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		BO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BO_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 3] = {
			-0.5f, 0.5f , 0.0f,
			0.5f , 0.5f , 0.0f,
			0.0f , -0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexArray->SetAttribPointer(0);



		unsigned indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position + 0.5;
				gl_Position = vec4(a_Position + 0.5,1.0);
			}
		
		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location=0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		
		)";

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
	}
	
	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BO_BIND_EVENT_FN(Application::OnWindowClosed));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}



	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.11f, 0.11f, 0.11f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
