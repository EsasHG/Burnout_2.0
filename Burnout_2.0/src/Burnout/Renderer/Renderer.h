#pragma once

#include "Burnout/Renderer/RenderCommand.h"
#include "Burnout/Cameras/Camera.h"
#include "Shader.h"
namespace Burnout
{
	class Renderer
	{
	public:

		static void Init();
		
		static void OnWindowResized(uint32_t width, uint32_t height);

		static void BeginScene(Camera& camera);
		static void BeginScene(Ref<Camera> camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& = glm::mat4(1.f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static Scope<SceneData> m_SceneData;
	};
}

