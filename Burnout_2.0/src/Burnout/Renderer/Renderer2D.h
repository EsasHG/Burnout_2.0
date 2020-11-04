#pragma once

#include "Burnout/Cameras/Camera.h"

#include "Texture.h"
#include "Burnout/Renderer/SubTexture2D.h"
namespace Burnout
{
	class Renderer2D 
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void Flush();


		//primitives
		static void DrawQuad(const glm::vec2& position, glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
		static void DrawQuad(const glm::vec3& position, glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
		static void DrawQuad(const glm::vec2& position, glm::vec2& size, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
		static void DrawQuad(const glm::vec3& position, glm::vec2& size, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));

		//rotation is in radians
		static void DrawRotatedQuad(const glm::vec2& position, glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
		static void DrawRotatedQuad(const glm::vec3& position, glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
		static void DrawRotatedQuad(const glm::vec2& position, glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
		static void DrawRotatedQuad(const glm::vec3& position, glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));

		//stats 
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();
	private:
		static void FlushAndReset();

	};
}