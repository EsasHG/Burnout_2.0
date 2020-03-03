#pragma once

#include "Layer.h"
#include <glm/mat4x4.hpp>

namespace Burnout
{
	class KeyPressedEvent;
	class Camera : public Layer
	{
	public:
		Camera(float aspectRatio, float FOV = 45.f, float nearPlane = 0.1f, float farPlane = 1000.f);
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event);
		bool OnKeyPressed(KeyPressedEvent& e);

		glm::mat4 GetViewProjMat();

		glm::mat4 m_ProjMat;
		glm::mat4 m_ViewMat;
	private:
		glm::vec3 m_Forward;
		glm::vec3 m_Pos;		
		float m_AspectRatio;
		float m_FOV;
		float m_NearPlane;
		float m_FarPlane;

	};
}

