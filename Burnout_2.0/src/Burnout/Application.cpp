#include "bopch.h"
#include "Application.h"

#include "Burnout/Log.h"

#include "Burnout/Renderer/Renderer.h"

#include "Input.h"

#include "Camera.h"

namespace Burnout
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		BO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BO_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		m_EditorCamera = new Camera(m_Window->GetWidth() / m_Window->GetHeight());
		PushLayer(m_EditorCamera);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, 0.5f , -0.5f, 1.0f, 0.f, 1.f, 1.f,
			0.0f , -0.5f, -0.5f, 1.0f, 1.f, 0.f, 1.f,
			0.5f , 0.5f , -0.5f, 0.0f, 0.f, 1.f, 1.f,
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned indices[3] = { 0,1,2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA.reset(VertexArray::Create());


		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,	 0.75f, 0.0f,
			-0.75f,	 0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned squareIndices[6] = { 0,1,2,2,3,0 };

		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		m_CubeVA.reset(VertexArray::Create());
		float cubeVertices[3 * 8]
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,	0.5f, 0.0f,
			-0.5f,	0.5f, 0.0f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,	0.5f, -0.5f,
			-0.5f,	0.5f, -0.5f
		};

		std::shared_ptr<VertexBuffer> cubeVB;
		cubeVB.reset(VertexBuffer::Create(cubeVertices, sizeof(squareVertices)));

		cubeVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
			});
		m_CubeVA->AddVertexBuffer(cubeVB);

		unsigned cubeIndices[6*2] = 
		{ 
			0,1,2,2,3,0,
			3,2,6,6,7,3,						
		};
		std::shared_ptr<IndexBuffer> cubeIB;
		cubeIB.reset(IndexBuffer::Create(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t)));
		m_CubeVA->SetIndexBuffer(cubeIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;
			
			uniform mat4 VPMat;
			
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Color = a_Color;
				v_Position  = a_Position;
				gl_Position =  VPMat* vec4(a_Position,1.0);
			}
		
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position, 1.0f);
			}
		
		)";

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;

			uniform mat4 VPMat;
			
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position =  a_Position;
				gl_Position = VPMat * vec4(a_Position,1.0);
			}
		
		)";
		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;


			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(0.2,0.3,0.8,1.0);
			}
		
		)";

		m_BlueShader.reset(Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));

	}
	
	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);

	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);

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
			RenderCommand::SetClearColor({ 0.11f, 0.11f, 0.11f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			m_Shader->UploadMat4Uniform("VPMat", m_EditorCamera->GetViewProjMat());
			Renderer::Submit(m_SquareVA);
			m_Shader->UploadMat4Uniform("VPMat", m_EditorCamera->GetViewProjMat());
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();
				
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
