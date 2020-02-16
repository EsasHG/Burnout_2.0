#pragma once

#include "Burnout/Renderer/GraphicsContext.h"

struct GLFWwindow;
namespace Burnout
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle = nullptr;
	};
}
