#pragma once

#include "CameraController.h"

#include "Burnout/Events/ApplicationEvent.h"
#include "Burnout/Events/MouseEvent.h"

namespace Burnout
{
	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};


	class OrthographicCameraController : public CameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool allowRotation = false);

		virtual void OnUpdate(Timestep& ts) override;
		virtual void OnEvent(Event& e) override;

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_ZoomLevel = 10.f;

		bool m_AllowRotation;
		float m_Rotation;
		float m_RotationSpeed = 180.f;
		OrthographicCameraBounds m_Bounds;
	};
}

