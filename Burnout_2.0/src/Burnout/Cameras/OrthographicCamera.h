#pragma once

#include "Camera.h"

namespace Burnout
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left = 0.f, float right = 100.f, float bottom = 0.f, float top = 100.f, float nearPlane = -1.f, float farPlane = 1.f);
		
		virtual void OnUpdate(Timestep ts) override;

		virtual void UpdatePosition(Timestep ts) override;


	private:
		float m_Rotation;
		float m_RotationSpeed;
	};
}

