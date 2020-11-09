#pragma once
#include "Burnout/Cameras/Camera.h"
namespace Burnout
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		float GetOrthographicSize() const { return m_OrthoGraphicSize; }
		void SetOrthographicSize(float size) { m_OrthoGraphicSize = size; RecalculateProjection(); }
	private:
		void RecalculateProjection();

		float m_OrthoGraphicSize = 10.f;
		float m_OrthoGraphicNear = -1.f, m_OrthoGraphicFar = 1.f;

		float m_AspectRatio = 0.0f;

	};
}