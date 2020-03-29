#include "bopch.h"
#include "OrthographicCameraController.h"
#include "Burnout/Input.h"
#include "Burnout/KeyCodes.h"

#include <glm/ext/matrix_clip_space.hpp>

#include <glm/ext/matrix_transform.hpp>


namespace Burnout
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool allowRotation)
		: CameraController(aspectRatio), m_AllowRotation(allowRotation), m_Rotation(0.f)
	{
		SetCameraProjMat(glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel));
	}

	void OrthographicCameraController::OnUpdate(Timestep& ts)
	{
		float time = ts;
		if (Input::IsKeyPressed(BO_KEY_W))
			m_Pos += glm::vec3(0.f, 1.f, 0.f) * m_TranslationSpeed * time;
		if (Input::IsKeyPressed(BO_KEY_A))
			m_Pos -= glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)) * m_TranslationSpeed * time;
		if (Input::IsKeyPressed(BO_KEY_S))
			m_Pos -= glm::vec3(0.f, 1.f, 0.f) * m_TranslationSpeed * time;
		if (Input::IsKeyPressed(BO_KEY_D))
			m_Pos += glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)) * m_TranslationSpeed * time;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(BO_KEY_Q))
				m_Rotation += m_RotationSpeed * ts;
			if (Input::IsKeyPressed(BO_KEY_E))
				m_Rotation -= m_RotationSpeed * ts;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Pos);
		SetCameraViewMat(glm::inverse(transform) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1)));
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BO_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BO_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.1;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

		m_TranslationSpeed = m_ZoomLevel * 2.f;
		
		SetCameraProjMat(glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f));
		
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		SetCameraProjMat(glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f));

		return false;
	}

}