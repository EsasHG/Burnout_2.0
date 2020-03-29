#pragma once

#include "Burnout/Layer.h"
#include <glm/mat4x4.hpp>

namespace Burnout
{
	class Camera
	{
	public:
		Camera() {}
		virtual ~Camera() = default;
		
		glm::mat4 GetViewProjMat() const { return  m_ProjMat * m_ViewMat; } 

	protected:
		friend class CameraController;

		glm::mat4 m_ProjMat = glm::mat4(1.f);
		glm::mat4 m_ViewMat = glm::mat4(1.f);

	};

}

