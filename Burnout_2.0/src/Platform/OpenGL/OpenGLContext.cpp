#include "bopch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Burnout
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		BO_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
		BO_CORE_ASSERT(status, "Failed to initialize Glad!");

		BO_CORE_INFO("OpenGL Vendor: {0}", glGetString(GL_VENDOR));
		BO_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
		BO_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));


		#ifdef BO_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			BO_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5!");
		#endif
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);

	}

}