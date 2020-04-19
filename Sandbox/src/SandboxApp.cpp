#include <Burnout.h>
#include <Burnout/Core/EntryPoint.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#include "Sandbox2D.h"

class ExampleLayer : public Burnout::Layer
{
public:
	ExampleLayer() : Layer()
	{
		BO_PROFILE_FUNCTION();

		m_PerspectiveCamera = std::make_shared<Burnout::FirstPersonCameraController>(1280.f / 720.f);
		m_OrthoCamera = std::make_shared<Burnout::OrthographicCameraController>(1280.f/720.f, true);
		m_ActiveCamera = m_OrthoCamera;

		m_VertexArray = Burnout::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f,  0.5f, -0.5f, 1.0f, 0.f, 1.f, 1.f,
			 0.0f, -0.5f, -0.5f, 1.0f, 1.f, 0.f, 1.f,
			 0.5f,  0.5f, -0.5f, 0.0f, 0.f, 1.f, 1.f,
		};

		Burnout::Ref<Burnout::VertexBuffer> vertexBuffer = Burnout::VertexBuffer::Create(vertices, sizeof(vertices));
		Burnout::BufferLayout layout = {
			{Burnout::ShaderDataType::Float3, "a_Position"},
			{Burnout::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned indices[3] = { 0,1,2 };
		Burnout::Ref<Burnout::IndexBuffer> indexBuffer;
		indexBuffer.reset(Burnout::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA = Burnout::VertexArray::Create();


		float squareVertices[5 * 4] = {
			-1.f, - 1.f, 0.0f, 0.f, 0.f,
			 1.f, - 1.f, 0.0f, 1.f, 0.f,
			 1.f,	1.f, 0.0f, 1.f, 1.f,
			-1.f,	1.f, 0.0f, 0.f, 1.f
		};


		Burnout::Ref<Burnout::VertexBuffer> squareVB = Burnout::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{Burnout::ShaderDataType::Float3, "a_Position"},
			{Burnout::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned squareIndices[6] = { 0,1,2,2,3,0 };

		Burnout::Ref<Burnout::IndexBuffer> squareIB;
		squareIB.reset(Burnout::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		m_CubeVA = Burnout::VertexArray::Create();
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

		Burnout::Ref<Burnout::VertexBuffer> cubeVB = Burnout::VertexBuffer::Create(cubeVertices, sizeof(squareVertices));

		cubeVB->SetLayout({
			{Burnout::ShaderDataType::Float3, "a_Position"}
			});
		m_CubeVA->AddVertexBuffer(cubeVB);

		unsigned cubeIndices[6 * 2] =
		{
			0,1,2,2,3,0,
			3,2,6,6,7,3,
		};
		Burnout::Ref<Burnout::IndexBuffer> cubeIB;
		cubeIB.reset(Burnout::IndexBuffer::Create(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t)));
		m_CubeVA->SetIndexBuffer(cubeIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_ModelMatrix;
			
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Color = a_Color;
				v_Position  = a_Position;
				gl_Position =  u_ViewProjection * u_ModelMatrix * vec4(a_Position,1.0);
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

		m_VertexPosColorShader = Burnout::Shader::Create("vertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_ModelMatrix;
			
			void main()
			{

				gl_Position = u_ViewProjection* u_ModelMatrix * vec4(a_Position,1.0);
			}
		
		)";
		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;
			uniform vec3 u_Color;

			void main() 
			{ 
				color = vec4(u_Color, 1.0);
			}
		
		)";

		m_FlatColorShader = Burnout::Shader::Create("flatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);


		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_Texture = Burnout::Texture2D::Create("assets/textures/me.png");
		m_LogoTexture = Burnout::Texture2D::Create("assets/textures/ChernoLogo.png");

		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);

	}

	void OnUpdate(Burnout::Timestep ts) override
	{
		BO_PROFILE_FUNCTION();

		m_ActiveCamera->OnUpdate(ts);

		Burnout::RenderCommand::SetClearColor({ 0.11f, 0.11f, 0.11f, 1 });
		Burnout::RenderCommand::Clear();

		Burnout::Renderer::BeginScene(m_ActiveCamera->GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 pos(x * 0.21f, y* 0.21f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Burnout::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind(0);

		Burnout::Renderer::Submit(textureShader, m_SquareVA,
			glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.1f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_LogoTexture->Bind();
		Burnout::Renderer::Submit(textureShader, m_SquareVA,
			glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.1f))* glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Triangle
		//Burnout::Renderer::Submit(m_Shader, m_VertexArray);
		
		Burnout::Renderer::EndScene();

	}
	virtual void OnImGuiRender() override
	{
		BO_PROFILE_FUNCTION();

		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Burnout::Event& event) override
	{
		BO_PROFILE_FUNCTION();

		m_ActiveCamera->OnEvent(event);
		Burnout::EventDispatcher d(event);
		d.Dispatch<Burnout::KeyPressedEvent>(BO_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
	}

	bool OnKeyPressed(Burnout::KeyPressedEvent& event)
	{
		BO_PROFILE_FUNCTION();

		if (event.GetKeyCode() == BO_KEY_SPACE)
		{
			if (m_ActiveCamera == m_PerspectiveCamera)
				m_ActiveCamera = m_OrthoCamera;
			else
				m_ActiveCamera = m_PerspectiveCamera;
		}
		return false;
	}


private:
	// ********** Cameras **********
	Burnout::Ref<Burnout::CameraController> m_ActiveCamera;
	Burnout::Ref<Burnout::FirstPersonCameraController> m_PerspectiveCamera;
	Burnout::Ref<Burnout::OrthographicCameraController> m_OrthoCamera;

	// ********** Rendering **********
	Burnout::ShaderLibrary m_ShaderLibrary;
	Burnout::Ref<Burnout::Shader> m_VertexPosColorShader;
	Burnout::Ref<Burnout::VertexArray> m_VertexArray;
	Burnout::Ref<Burnout::Shader> m_FlatColorShader;
	Burnout::Ref<Burnout::VertexArray> m_SquareVA;

	Burnout::Ref<Burnout::Texture2D> m_Texture, m_LogoTexture;

	Burnout::Ref<Burnout::VertexArray> m_CubeVA;

	glm::vec3 m_SquareColor = { 0.2,0.3,0.8 };

};

class Sandbox : public Burnout::Application
{
public: 
	Sandbox()
	{
		ExampleLayer* l = new ExampleLayer();
		PushLayer(l);
		//PushLayer(new Sandbox2D());

	}
	~Sandbox()
	{

	}

};
Burnout::Application* Burnout::CreateApplication()
{
	return new Sandbox();
}