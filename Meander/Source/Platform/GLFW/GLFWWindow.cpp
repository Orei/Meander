#include "pch.h"
#include "GLFWWindow.h"
#include "Meander/Input/Input.h"
#include <GLFW/glfw3.h>

namespace Meander
{
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

		glfwSetErrorCallback([](int error, const char* description)
		{
			MN_ERROR("GLFW Error: %s\n", description);
		});
		
		glfwSetKeyCallback(m_NativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Input::SetKeyState((Key)key, (InputAction)action);
		});
		
		glfwSetMouseButtonCallback(m_NativeWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			Input::SetMouseButtonState((MouseButton)button, (InputAction)action);
		});
		
		glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow* window, double xpos, double ypos)
		{
			Input::SetMousePosition({ (float)xpos, (float)ypos });
		});
		
		glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* const window, int width, int height)
		{
			Window::Get()->Resize(width, height);
		});
	}

	void GLFWWindow::SetVerticalSync(bool enabled)
	{
		glfwSwapInterval(enabled);
	}

	void GLFWWindow::SetCursorState(bool enabled)
	{
		glfwSetInputMode(m_NativeWindow, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
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

	void GLFWWindow::Resize(unsigned int width, unsigned int height)
	{
		s_Properties.Width = width;
		s_Properties.Height = height;

		if (m_OnResize != nullptr)
			m_OnResize(width, height);
	}
}