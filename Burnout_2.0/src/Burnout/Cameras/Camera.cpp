#include "bopch.h"
#include "Camera.h"
#include "Burnout/KeyCodes.h"
#include "Burnout/Input.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Burnout
{

	Camera::Camera(float nearPlane, float farPlane)
		: m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		m_Forward = glm::vec3(0.f, 0.f, -1.f);
		m_Pos = glm::vec3(0.0f, 0.f, 3.f);

		m_ProjMat = glm::mat4(1.f);
		m_ViewMat = glm::mat4(1.f);
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
		float speed = 0.01;

		if (Input::IsKeyPressed(BO_KEY_W))
			m_Pos += glm::vec3(0.f, 0.f, -speed);
		if (Input::IsKeyPressed(BO_KEY_A))
			m_Pos += glm::vec3(-speed, 0.f, 0.f);
		if (Input::IsKeyPressed(BO_KEY_S))
			m_Pos += glm::vec3(0.f, 0.f, speed);
		if (Input::IsKeyPressed(BO_KEY_D))
			m_Pos += glm::vec3(speed, 0.f, 0.0f);

		if (Input::IsKeyPressed(BO_KEY_E))
			m_Pos += glm::vec3(0.f, speed, 0.0f);
		if (Input::IsKeyPressed(BO_KEY_Q))
			m_Pos += glm::vec3(0.f, -speed, 0.f);
	}

	void Camera::UpdateProjMatrix(float newAspectRatio)
	{
	}

	glm::mat4 Camera::GetViewProjMat()
	{
		return  m_ProjMat * m_ViewMat;
	}
}