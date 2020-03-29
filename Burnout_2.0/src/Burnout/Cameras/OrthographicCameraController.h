#pragma once

#include "CameraController.h"

#include "Burnout/Events/ApplicationEvent.h"
#include "Burnout/Events/MouseEvent.h"

namespace Burnout
{

	class OrthographicCameraController : public CameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool allowRotation = false);

		virtual void OnUpdate(Timestep& ts) override;
		virtual void OnEvent(Event& e) override;

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_ZoomLevel = 1.f;

		bool m_AllowRotation;
		float m_Rotation;
		float m_RotationSpeed = 180.f;

	};
}

