#include "bopch.h"
#include "OrthographicCamera.h"
#include "Burnout/Input.h"
#include "Burnout/KeyCodes.h"

#include <glm/ext/matrix_clip_space.hpp>

#include <glm/ext/matrix_transform.hpp>

namespace Burnout
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearPlane, float farPlane)
		: Camera(nearPlane, farPlane), m_Rotation(0), m_RotationSpeed(180.0f)
	{
		m_ProjMat = glm::ortho(left, right, bottom, top, m_NearPlane, m_FarPlane);
	}

	void OrthographicCamera::OnUpdate(Timestep ts)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Pos);
		m_ViewMat = glm::inverse(transform)* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		UpdatePosition(ts);
	}
	void OrthographicCamera::UpdatePosition(Timestep ts)
	{
		float time = ts;
		if (Input::IsKeyPressed(BO_KEY_W))
			m_Pos += glm::vec3(0.f,1.f,0.f) * m_Speed * time;
		if (Input::IsKeyPressed(BO_KEY_A))
			m_Pos -= glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)) * m_Speed * time;
		if (Input::IsKeyPressed(BO_KEY_S))
			m_Pos -= glm::vec3(0.f, 1.f, 0.f) * m_Speed * time;
		if (Input::IsKeyPressed(BO_KEY_D))
			m_Pos += glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)) * m_Speed * time;

		if (Input::IsKeyPressed(BO_KEY_Q))
			m_Rotation += m_RotationSpeed * ts;
		if (Input::IsKeyPressed(BO_KEY_E))
			m_Rotation -= m_RotationSpeed * ts;
	}


}