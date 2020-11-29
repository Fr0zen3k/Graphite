#include "Graphite/Core/grpch.h"

#include "Input.h"

namespace Graphite
{
	bool Input::grIsKeyPressed(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	
	bool Input::grIsMouseButtonPressed(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, keycode);
		return state == GLFW_PRESS;
	}
	
	bool Input::grIsMouseInWindow()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
		auto [x, y] = grGetMousePosition();
		return x < 0 || y < 0;
	}

	std::pair<double, double> Input::grGetMousePosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return std::pair<double, double>(xPos, yPos);
	}
	
}