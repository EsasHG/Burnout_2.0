#include "bopch.h"
#include "PerspectiveCamera.h"

#include <glm/ext/matrix_clip_space.hpp>

namespace Burnout
{

	PerspectiveCamera::PerspectiveCamera(float aspectRatio, float FOV, float nearPlane, float farPlane)
		: m_AspectRatio(aspectRatio), m_FOV(FOV), Camera(nearPlane, farPlane)
	{
		m_ProjMat = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);

	}
	void PerspectiveCamera::UpdateProjMatrix(float newAspectRatio)
	{
		m_AspectRatio = newAspectRatio;
		m_ProjMat = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
		BO_CORE_TRACE("ProjMat Updated! {0}", m_AspectRatio);

	}
}
