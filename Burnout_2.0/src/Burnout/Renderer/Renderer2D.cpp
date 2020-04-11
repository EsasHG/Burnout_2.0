#include "bopch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"	

#include "RenderCommand.h"	

#include <glm/gtc/matrix_transform.hpp> 

namespace Burnout
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Data;
	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();

		s_Data->QuadVertexArray = VertexArray::Create();


		float squareVertices[5 * 4] = {
			-1.f, -1.f, 0.0f,
			 1.f, -1.f, 0.0f,
			 1.f,	1.f, 0.0f,
			-1.f,	1.f, 0.0f,
		};


		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		unsigned squareIndices[6] = { 0,1,2,2,3,0 };

		Ref<Burnout::IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}
	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const Camera& camera)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjMat());

	}
	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y, 0.f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, glm::vec2& size, const glm::vec4& color)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) /*rotation*/
			* glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		
		s_Data->FlatColorShader->SetMat4("u_ModelMatrix", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}
