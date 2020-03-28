#include "bopch.h"
#include "Camera.h"
#include "Burnout/Input.h"
#include "Burnout/Events/MouseEvent.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Burnout
{

	Camera::Camera(float nearPlane, float farPlane)
		: m_NearPlane(nearPlane), m_FarPlane(farPlane), m_Pos({ 0.f,0.f,0.f })
	{

		m_ProjMat = glm::mat4(1.f);
		m_ViewMat = glm::mat4(1.f);
		m_Speed = 5.0;
	}

	glm::mat4 Camera::GetViewProjMat()
	{
		return  m_ProjMat * m_ViewMat;
	}

	void Camera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(BO_BIND_EVENT_FN(Camera::OnMouseScrolled));
	}

	bool Camera::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_Speed += event.GetYOffset()* 0.01;
		if (m_Speed < 0.f)
			m_Speed = 0.0001f;
		return false;
	}
}