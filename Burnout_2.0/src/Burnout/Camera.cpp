#include "bopch.h"
#include "Camera.h"
#include "KeyCodes.h"
#include "Events/KeyEvent.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Burnout
{

	Camera::Camera(float aspectRatio, float FOV, float nearPlane, float farPlane)
		: m_AspectRatio(aspectRatio), m_FOV(FOV), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		m_Forward = glm::vec3(0.f, 0.f, -1.f);
		m_Pos = glm::vec3(0.0f, 0.f, 3.f);

		m_ProjMat = glm::mat4(1.f);
		m_ViewMat = glm::mat4(1.f);
		m_ProjMat = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane,m_FarPlane);

		//// pass projection matrix to shader (note that in this case it could change every frame)
		//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		//ourShader.setMat4("projection", projection);
	}

	void Camera::OnUpdate()
	{
		//std::cout << pos.x << ", " << pos.y << ", " << pos.z << "\n";
		m_ViewMat = glm::lookAt(m_Pos, m_Pos + m_Forward, glm::vec3(0.f, 1.f, 0.f));
		//m_ViewMat = glm::lookAt(m_Pos, { 0,0,0 }, glm::vec3(0.f, 1.f, 0.f));


		//return glm::lookAt(Position, Position + Front, Up);
	}

	void Camera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(BO_BIND_EVENT_FN(Camera::OnKeyPressed));
	}

	glm::mat4 Camera::GetViewProjMat()
	{
		return  m_ProjMat * m_ViewMat;
	}

	bool Camera::OnKeyPressed(KeyPressedEvent& e)
	{

		float speed = 0.01;
		if (e.GetKeyCode() == BO_KEY_W)
			m_Pos += glm::vec3(0.f, 0.f, -speed);
		if (e.GetKeyCode() == BO_KEY_A)
			m_Pos += glm::vec3(-speed, 0.f, 0.f);
		if(e.GetKeyCode() == BO_KEY_S)
			m_Pos += glm::vec3(0.f, 0.f, speed);
		if (e.GetKeyCode() == BO_KEY_D)
			m_Pos += glm::vec3(speed, 0.f, 0.0f);

		if (e.GetKeyCode() == BO_KEY_E)
			m_Pos += glm::vec3(0.f, speed, 0.0f);
		if (e.GetKeyCode() == BO_KEY_Q)
			m_Pos += glm::vec3(0.f, -speed, 0.f);
		
		return false;
	}

}