#include "pch.h"
#include "GLFWWindow.h"
#include "Meander/Input/Input.h"
#include <GLFW/glfw3.h>

namespace Meander
{
	/* Callbacks */
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Input::SetKeyState((Key)key, (InputAction)action);
	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Input::SetMouseButtonState((MouseButton)button, (InputAction)action);
	}

	static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Input::SetMousePosition({ (float)xpos, (float)ypos });
	}

	void ErrorCallback(int error, const char* description)
	{
		MN_ERROR("GLFW Error: %s\n", description);
	}
	/* Callbacks */

	void GLFWWindow::Initialize(const WindowProperties& properties)
	{
		MN_INFO("Creating GLFW window...");

		s_Properties = properties;

		int status = glfwInit();
		MN_ASSERT(status,"Unable to initialize GLFW.");

		m_NativeWindow = glfwCreateWindow(properties.Width, properties.Height, properties.Title, nullptr, nullptr);

		if (m_NativeWindow == nullptr)
		{
			MN_ASSERT(false, "Unable to create GLFW window.");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_NativeWindow);

		glfwSetErrorCallback(ErrorCallback);
		glfwSetKeyCallback(m_NativeWindow, KeyCallback);
		glfwSetMouseButtonCallback(m_NativeWindow, MouseButtonCallback);
		glfwSetCursorPosCallback(m_NativeWindow, MousePositionCallback);
	}

	void GLFWWindow::SetVerticalSync(bool enabled)
	{
		glfwSwapInterval(enabled);
	}

	void GLFWWindow::PollEvents()
	{
		glfwPollEvents();
	}

	void GLFWWindow::Present()
	{
		glfwSwapBuffers(m_NativeWindow);
	}

	bool GLFWWindow::IsClosing()
	{
		return glfwWindowShouldClose(m_NativeWindow);
	}

	void* GLFWWindow::GetProcessAddress()
	{
		return glfwGetProcAddress;
	}
}