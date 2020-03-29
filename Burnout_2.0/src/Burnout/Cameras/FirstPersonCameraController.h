#pragma once

#include "Burnout/Cameras/CameraController.h"

#include "Burnout/Events/ApplicationEvent.h"
#include "Burnout/Events/MouseEvent.h"

namespace Burnout
{
	class FirstPersonCameraController : public CameraController
	{
	public:
		FirstPersonCameraController(float aspectRatio, float FOV = 45.f, float nearPlane = 0.1f, float farPlane = 1000.f);
		virtual ~FirstPersonCameraController() {}

		// ********** Overrides **********
		virtual void OnUpdate(Timestep& ts) override;

		// ********** Events **********
		virtual void OnEvent(Event& e) override;

		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	protected:

		glm::vec3 m_Forward;
		glm::vec3 m_Up;
		glm::vec3 m_Right;

		float m_FOV;

		bool m_FirstMouse = true;

		float m_LastX;
		float m_LastY;

		float m_Yaw;
		float m_Pitch;
	
	};
}

