#include "bopch.h"
#include "Renderer.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

namespace Burnout
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjMat();

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("VPMat", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ModelMatrix", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


}
