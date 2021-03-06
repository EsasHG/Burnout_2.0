#include "bopch.h"
#include "WindowsInput.h"

#include "Burnout/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Burnout
{
	Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window , keycode);
		return  state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return  state == GLFW_PRESS;

		return false;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos,  (float)ypos };

	}
	float WindowsInput::GetMouseXImpl()
	{
		GetMousePositionImpl();
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl()
	{
		GetMousePositionImpl();
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
