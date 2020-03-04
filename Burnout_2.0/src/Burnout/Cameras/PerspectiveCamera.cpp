#include "bopch.h"
#include "PerspectiveCamera.h"

#include "Burnout/Events/MouseEvent.h"
#include "Burnout/Input.h"
#include "Burnout/MouseButtonCodes.h"

#include <glm/ext/matrix_clip_space.hpp>

namespace Burnout
{

	PerspectiveCamera::PerspectiveCamera(float aspectRatio, float FOV, float nearPlane, float farPlane)
		: m_AspectRatio(aspectRatio), m_FOV(FOV), m_LastX(0.f), m_LastY(0.f), m_Yaw(-90.f), m_Pitch(0.f), Camera(nearPlane, farPlane)
	{
		m_ProjMat = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);

	}
	void PerspectiveCamera::UpdateProjMatrix(float newAspectRatio)
	{
		m_AspectRatio = newAspectRatio;
		m_ProjMat = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
		//BO_CORE_TRACE("ProjMat Updated! {0}", m_AspectRatio);

	}

	void PerspectiveCamera::OnEvent(Event& event)  
	{
		Camera::OnEvent(event);
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseMovedEvent>(BO_BIND_EVENT_FN(PerspectiveCamera::OnMouseMoved));
	
	};

	bool PerspectiveCamera::OnMouseMoved(MouseMovedEvent& event)
	{

		if (!Input::IsMouseButtonPressed(BO_MOUSE_BUTTON_RIGHT))
		{
			m_FirstMouse = true;
			return false;
		}

		if (m_FirstMouse)
		{
			m_LastX = event.GetX();
			m_LastY = event.GetY();
			m_FirstMouse = false;
		}

		float xoffset = event.GetX() - m_LastX;
		float yoffset = m_LastY - event.GetY();;
		m_LastX = event.GetX();
		m_LastY = event.GetY();;

		float sensitivity = 0.05;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Forward = glm::normalize(direction);
		return true;
	}
}
