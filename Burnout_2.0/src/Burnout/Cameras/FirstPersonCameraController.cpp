#include "bopch.h"
#include "FirstPersonCameraController.h"

#include "Burnout/Events/MouseEvent.h"
#include "Burnout/Events/ApplicationEvent.h"
#include "Burnout/Input.h"
#include "Burnout/KeyCodes.h"
#include "Burnout/MouseButtonCodes.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Burnout
{

	FirstPersonCameraController::FirstPersonCameraController(float aspectRatio, float FOV, float nearPlane, float farPlane)
		: CameraController(aspectRatio), m_FOV(FOV), m_LastX(0.f), m_LastY(0.f), m_Yaw(-90.f), m_Pitch(0.f)
	{
		m_Forward = glm::vec3(0.f, 0.f, -1.f);
		m_Right = glm::vec3(1.f, 0.f, 0.f);
		m_Pos = glm::vec3(0.0f, 0.f, 3.f);
		m_Up = glm::vec3(0.f, 1.f, 0.f);

		SetCameraProjMat(glm::perspective(glm::radians(m_FOV), m_AspectRatio, nearPlane, farPlane));
		SetCameraViewMat(glm::lookAt(m_Pos, m_Pos + m_Forward, glm::vec3(0.f, 1.f, 0.f)));

	}

	void FirstPersonCameraController::OnUpdate(Timestep& ts)
	{
		float time = ts;
	
		if (Input::IsKeyPressed(BO_KEY_W))
			m_Pos += m_Forward * m_TranslationSpeed * time;
		if (Input::IsKeyPressed(BO_KEY_A))
			m_Pos -= m_Right * m_TranslationSpeed * time;
		if (Input::IsKeyPressed(BO_KEY_S))
			m_Pos -= m_Forward * m_TranslationSpeed * time;
		if (Input::IsKeyPressed(BO_KEY_D))
			m_Pos += m_Right * m_TranslationSpeed * time;

		if (Input::IsKeyPressed(BO_KEY_E))
			m_Pos += m_Up * m_TranslationSpeed * time;
		if (Input::IsKeyPressed(BO_KEY_Q))
			m_Pos -= m_Up * m_TranslationSpeed * time;

		m_Right = glm::cross(m_Forward, m_Up);

		SetCameraViewMat(glm::lookAt(m_Pos, m_Pos + m_Forward, glm::vec3(0.f, 1.f, 0.f)));
	}

	void FirstPersonCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseMovedEvent>(BO_BIND_EVENT_FN(FirstPersonCameraController::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(BO_BIND_EVENT_FN(FirstPersonCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BO_BIND_EVENT_FN(FirstPersonCameraController::OnWindowResized));
	};

	bool FirstPersonCameraController::OnMouseMoved(MouseMovedEvent& e)
	{

		if (!Input::IsMouseButtonPressed(BO_MOUSE_BUTTON_RIGHT))
		{
			m_FirstMouse = true;
			return false;
		}

		if (m_FirstMouse)
		{
			m_LastX = e.GetX();
			m_LastY = e.GetY();
			m_FirstMouse = false;
		}

		float xoffset = e.GetX() - m_LastX;
		float yoffset = m_LastY - e.GetY();;
		m_LastX = e.GetX();
		m_LastY = e.GetY();;

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

	bool FirstPersonCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_TranslationSpeed -= e.GetYOffset();
		m_TranslationSpeed = std::max(m_TranslationSpeed, 0.001f);
		return false;
	}

	bool FirstPersonCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		if (e.GetHeight() != 0)
		{
			m_AspectRatio = (float)e.GetWidth()/(float)e.GetHeight();
			SetCameraProjMat(glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.1f, 1000.f));
		}

		return false;
	}
}
