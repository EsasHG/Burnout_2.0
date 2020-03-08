#include <Burnout.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "imgui/imgui.h"

class ExampleLayer : public Burnout::Layer
{
public:
	ExampleLayer()
		:Layer(), m_EditorCamera(16.f / 9.f)
	{


		m_VertexArray.reset(Burnout::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,  0.5f, -0.5f, 1.0f, 0.f, 1.f, 1.f,
			 0.0f, -0.5f, -0.5f, 1.0f, 1.f, 0.f, 1.f,
			 0.5f,  0.5f, -0.5f, 0.0f, 0.f, 1.f, 1.f,
		};

		std::shared_ptr<Burnout::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Burnout::VertexBuffer::Create(vertices, sizeof(vertices)));
		Burnout::BufferLayout layout = {
			{Burnout::ShaderDataType::Float3, "a_Position"},
			{Burnout::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned indices[3] = { 0,1,2 };
		std::shared_ptr<Burnout::IndexBuffer> indexBuffer;
		indexBuffer.reset(Burnout::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA.reset(Burnout::VertexArray::Create());


		float squareVertices[3 * 4] = {
			-1.f, - 1.f, 0.0f,
			 1.f, - 1.f, 0.0f,
			 1.f,	1.f, 0.0f,
			-1.f,	1.f, 0.0f
		};

		std::shared_ptr<Burnout::VertexBuffer> squareVB;
		squareVB.reset(Burnout::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{Burnout::ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned squareIndices[6] = { 0,1,2,2,3,0 };

		std::shared_ptr<Burnout::IndexBuffer> squareIB;
		squareIB.reset(Burnout::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		m_CubeVA.reset(Burnout::VertexArray::Create());
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

		std::shared_ptr<Burnout::VertexBuffer> cubeVB;
		cubeVB.reset(Burnout::VertexBuffer::Create(cubeVertices, sizeof(squareVertices)));

		cubeVB->SetLayout({
			{Burnout::ShaderDataType::Float3, "a_Position"}
			});
		m_CubeVA->AddVertexBuffer(cubeVB);

		unsigned cubeIndices[6 * 2] =
		{
			0,1,2,2,3,0,
			3,2,6,6,7,3,
		};
		std::shared_ptr<Burnout::IndexBuffer> cubeIB;
		cubeIB.reset(Burnout::IndexBuffer::Create(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t)));
		m_CubeVA->SetIndexBuffer(cubeIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;
			
			uniform mat4 VPMat;
			uniform mat4 u_ModelMatrix;
			
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Color = a_Color;
				v_Position  = a_Position;
				gl_Position =  VPMat * u_ModelMatrix * vec4(a_Position,1.0);
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

		m_Shader.reset(Burnout::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;

			uniform mat4 VPMat;
			uniform mat4 u_ModelMatrix;
			
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position =  a_Position;
				gl_Position = VPMat* u_ModelMatrix * vec4(a_Position,1.0);
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

		m_BlueShader.reset(Burnout::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Burnout::Timestep ts) override
	{
		//BO_TRACE("DeltaTime: {0}s, {1}ms", ts.GetSeconds(), ts.GetMilliseconds());

		Burnout::RenderCommand::SetClearColor({ 0.11f, 0.11f, 0.11f, 1 });
		Burnout::RenderCommand::Clear();
		Burnout::Renderer::BeginScene(m_EditorCamera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.21f, y* 0.21f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Burnout::Renderer::Submit(m_BlueShader, m_SquareVA, transform);

			}
		}
		Burnout::Renderer::Submit(m_Shader, m_VertexArray);
		
		Burnout::Renderer::EndScene();
		m_EditorCamera.OnUpdate(ts);

	}
	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Burnout::Event& event) override
	{
		m_EditorCamera.OnEvent(event);
	}
	Burnout::PerspectiveCamera m_EditorCamera;
private:

	std::shared_ptr<Burnout::Shader> m_Shader;
	std::shared_ptr<Burnout::VertexArray> m_VertexArray;

	std::shared_ptr<Burnout::Shader> m_BlueShader;
	std::shared_ptr<Burnout::VertexArray> m_SquareVA;

	std::shared_ptr<Burnout::VertexArray> m_CubeVA;

};

class Sandbox : public Burnout::Application
{
public: 
	Sandbox()
	{
		ExampleLayer* l = new ExampleLayer();
		PushLayer(l);
		//Burnout::Application::PushLayer(&l->m_EditorCamera);

	}
	~Sandbox()
	{

	}

};
Burnout::Application* Burnout::CreateApplication()
{
	return new Sandbox();
}