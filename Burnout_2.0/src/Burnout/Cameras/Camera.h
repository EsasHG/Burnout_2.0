#pragma once

#include "Burnout/Core/Layer.h"
#include <glm/mat4x4.hpp>

namespace Burnout
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			: m_ProjMat(projection) {}
		virtual ~Camera() = default;
		

		const glm::mat4& GetProjection() const { return m_ProjMat; }
		glm::mat4 GetViewProjMat() const { return  m_ProjMat * m_ViewMat; } 

	protected:
		friend class CameraController;

		glm::mat4 m_ProjMat = glm::mat4(1.f);
		glm::mat4 m_ViewMat = glm::mat4(1.f);

	};

}

