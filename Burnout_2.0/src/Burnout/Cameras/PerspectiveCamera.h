#pragma once

#include "Camera.h"
namespace Burnout
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float aspectRatio, float FOV = 45.f, float nearPlane = 0.1f, float farPlane = 1000.f);

		virtual void UpdateProjMatrix(float newAspectRatio) override;

	protected:
		float m_AspectRatio;
		float m_FOV;
	};
}

