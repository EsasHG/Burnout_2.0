#include "bopch.h"
#include "OrthographicCamera.h"
#include <glm/ext/matrix_clip_space.hpp>


namespace Burnout
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearPlane, float farPlane)
		: Camera(nearPlane, farPlane)
	{
		m_ProjMat = glm::ortho(left, right, bottom, top, m_NearPlane, m_FarPlane);
	}
	glm::mat4 OrthographicCamera::GetViewProjMat()
	{
		return m_ProjMat;
	}
}