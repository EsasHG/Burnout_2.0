#pragma once

#include "Burnout/Cameras/Camera.h"
namespace Burnout
{
	class Renderer2D 
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void EndScene();


		//primitives
		static void DrawQuad(const glm::vec2& position, glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, glm::vec2& size, const glm::vec4& color);
	};
}