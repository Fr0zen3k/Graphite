#include "Graphite/Core/grpch.h"

#include "Input.h"

namespace Graphite
{
	bool Input::IsKeyPressed(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	
	bool Input::IsMouseButtonPressed(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
		auto state = glfwGetMouseButton(window, keycode);
		return state == GLFW_PRESS;
	}
	
	bool Input::IsMouseInWindow()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
		auto [x, y] = GetMousePosition();
		return x < 0 || y < 0;
	}

	std::pair<double, double> Input::GetMousePosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return std::pair<double, double>(xPos, yPos);
	}
	
}