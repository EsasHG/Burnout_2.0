#include "bopch.h"
#include "SceneCamera.h"


#include <glm/gtc/matrix_transform.hpp>
namespace Burnout
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_OrthoGraphicSize = size;
		m_OrthoGraphicNear = nearClip;
		m_OrthoGraphicFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
		
	}
	void SceneCamera::RecalculateProjection()
	{
		float orthoLeft = -m_OrthoGraphicSize * m_AspectRatio * 0.5f;
		float orthoRight = m_OrthoGraphicSize * m_AspectRatio * 0.5f;
		float orthoBottom = -m_OrthoGraphicSize * 0.5f;
		float orthoTop = m_OrthoGraphicSize * 0.5f;

		m_ProjMat = glm::ortho(orthoLeft, orthoRight,
			orthoBottom, orthoTop,
			m_OrthoGraphicNear, m_OrthoGraphicFar);
	}
}