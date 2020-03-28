#pragma once

#include "Camera.h"

namespace Burnout
{
	class MouseMovedEvent;
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float aspectRatio, float FOV = 45.f, float nearPlane = 0.1f, float farPlane = 1000.f);
		virtual ~PerspectiveCamera() {}

		// ********** Overrides **********
		virtual void OnUpdate(Timestep ts) override;

		virtual void UpdatePosition(Timestep ts) override;

		virtual void UpdateProjMatrix(float newAspectRatio) override;

		// ********** Events **********
		virtual void OnEvent(Event& event) override;
		bool OnMouseMoved(MouseMovedEvent& event);



	protected:

		glm::vec3 m_Forward;
		glm::vec3 m_Up;

		float m_AspectRatio;
		float m_FOV;

		bool m_FirstMouse = true;

		float m_LastX;
		float m_LastY;

		float m_Yaw;
		float m_Pitch;
	
	};
}

