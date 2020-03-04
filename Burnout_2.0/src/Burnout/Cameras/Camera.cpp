#include "bopch.h"
#include "Camera.h"
#include "Burnout/KeyCodes.h"
#include "Burnout/Input.h"
#include "Burnout/Events/MouseEvent.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Burnout
{

	Camera::Camera(float nearPlane, float farPlane)
		: m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		m_Forward = glm::vec3(0.f, 0.f, -1.f);
		m_Pos = glm::vec3(0.0f, 0.f, 3.f);
		m_Up = glm::vec3(0.f, 1.f, 0.f);

		m_ProjMat = glm::mat4(1.f);
		m_ViewMat = glm::mat4(1.f);
		m_Speed = 0.01;
	}

	void Camera::OnUpdate()
	{
		//std::cout << pos.x << ", " << pos.y << ", " << pos.z << "\n";
		m_ViewMat = glm::lookAt(m_Pos, m_Pos + m_Forward, glm::vec3(0.f, 1.f, 0.f));
		//m_ViewMat = glm::lookAt(m_Pos, { 0,0,0 }, glm::vec3(0.f, 1.f, 0.f));
		//return glm::lookAt(Position, Position + Front, Up);

		CheckMovement();
	}

	void Camera::CheckMovement()
	{
		if (Input::IsKeyPressed(BO_KEY_W))
			m_Pos += m_Forward * m_Speed;
		if (Input::IsKeyPressed(BO_KEY_A))
			m_Pos -= glm::cross(m_Forward , m_Up) * m_Speed;
		if (Input::IsKeyPressed(BO_KEY_S))
			m_Pos -= m_Forward * m_Speed;
		if (Input::IsKeyPressed(BO_KEY_D))
			m_Pos += glm::cross(m_Forward, m_Up) * m_Speed;

		if (Input::IsKeyPressed(BO_KEY_E))
			m_Pos += m_Up * m_Speed;
		if (Input::IsKeyPressed(BO_KEY_Q))
			m_Pos -= m_Up * m_Speed;
	}

	void Camera::UpdateProjMatrix(float newAspectRatio)
	{
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
		BO_CORE_TRACE("X: {0}, Y: {1}, Speed: {2}", event.GetXOffset(), event.GetYOffset(), m_Speed);
		if (m_Speed < 0.f)
			m_Speed = 0.0001f;
		return false;
	}
}