#include "bopch.h"
#include "Renderer.h"

#include <glm/ext/matrix_clip_space.hpp>

namespace Burnout
{
	void Renderer::BeginScene()
	{
		glm::mat4 proj = glm::perspective(35.0f, 1.0f, 0.1f, 100.0f);
		glm::mat4 view;
		//BO_CORE_TRACE("proj mat: {0}", proj);
		//BO_CORE_TRACE("view mat: {0}", view);
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


}
