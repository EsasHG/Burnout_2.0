#pragma once

#include "Burnout/Layer.h"
#include <glm/mat4x4.hpp>

namespace Burnout
{
	class KeyPressedEvent;
	class Camera : public Layer
	{
	public:
		Camera(float nearPlane = 0.1f, float farPlane = 1000.f);
		virtual void OnUpdate() override;
		void CheckMovement();

		virtual void UpdateProjMatrix(float newAspectRatio);

		virtual glm::mat4 GetViewProjMat();

		glm::mat4 m_ProjMat;
		glm::mat4 m_ViewMat;
	protected:
		glm::vec3 m_Forward;
		glm::vec3 m_Pos;
		float m_NearPlane;
		float m_FarPlane;

	};
}

