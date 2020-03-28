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
		Camera(float nearPlane = -0.1f, float farPlane = 1000.f);
		virtual ~Camera() = default;

		virtual void OnUpdate(Timestep ts) = 0;
		virtual void UpdatePosition(Timestep ts) = 0;

		virtual void UpdateProjMatrix(float newAspectRatio) {};

		glm::mat4 GetViewProjMat();

		// ********** Events **********
		virtual void OnEvent(Event& event);

		bool OnMouseScrolled(MouseScrolledEvent& event);

		const glm::vec3& GetPosition() const { return m_Pos; }
		void SetPosition(const glm::vec3& position) { m_Pos = position; }

	protected:
		glm::mat4 m_ProjMat;
		glm::mat4 m_ViewMat;
		glm::vec3 m_Pos;

		float m_NearPlane;
		float m_FarPlane;
		float m_Speed;


	};
}

