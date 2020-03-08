#include "bopch.h"
#include "Renderer.h"

#include <glm/ext/matrix_clip_space.hpp>

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
		shader->UploadMat4Uniform("VPMat", m_SceneData->ViewProjectionMatrix);
		shader->UploadMat4Uniform("u_ModelMatrix", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


}
