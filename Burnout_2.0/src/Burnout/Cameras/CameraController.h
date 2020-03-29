#pragma once
#include "Camera.h"

#include "Burnout/Core/Timestep.h"

namespace Burnout
{
	class CameraController
	{
	public:
		CameraController(float aspectRatio) : m_AspectRatio(aspectRatio) {}
		
		virtual ~CameraController() = default;

		virtual void OnUpdate(Timestep& ts) = 0;
		virtual void OnEvent(Event& e) = 0;

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		void SetCameraViewMat(const glm::mat4& mat) { m_Camera.m_ViewMat = mat;}
		void SetCameraProjMat(const glm::mat4& mat) { m_Camera.m_ProjMat = mat; }

	protected:

		float m_AspectRatio;
		glm::vec3 m_Pos = glm::vec3(0.f, 0.f, 0.f);

		float m_TranslationSpeed = 5.f;

		Camera m_Camera;
	};

}