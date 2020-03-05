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
		virtual void UpdateProjMatrix(float newAspectRatio) override;
		virtual void OnEvent(Event& event) override;
		bool OnMouseMoved(MouseMovedEvent& event);
	protected:
		float m_AspectRatio;
		float m_FOV;

		bool m_FirstMouse = true;

		float m_LastX;
		float m_LastY;

		float m_Yaw;
		float m_Pitch;
	
	};
}

