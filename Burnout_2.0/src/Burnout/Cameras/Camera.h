#pragma once

#include "Burnout/Layer.h"
#include <glm/mat4x4.hpp>

namespace Burnout
{
	class KeyPressedEvent;
	class MouseScrolledEvent;
	class Camera //: public Layer
	{
	public:
		Camera(float nearPlane = 0.1f, float farPlane = 1000.f);

		const glm::vec3& GetPosition() const { return m_Pos; }
		void SetPosition(const glm::vec3& position) { m_Pos = position; }
		virtual void OnUpdate(Timestep ts);
		void CheckMovement(Timestep ts);

		virtual void UpdateProjMatrix(float newAspectRatio);

		virtual glm::mat4 GetViewProjMat();
		virtual void OnEvent(Event& event);

		bool OnMouseScrolled(MouseScrolledEvent& event);

		glm::mat4 m_ProjMat;
		glm::mat4 m_ViewMat;
	protected:
		glm::vec3 m_Forward;
		glm::vec3 m_Up;
		glm::vec3 m_Pos;
		float m_NearPlane;
		float m_FarPlane;
		float m_Speed;


	};
}

