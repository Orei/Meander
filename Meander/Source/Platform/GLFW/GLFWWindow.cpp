#include "pch.h"
#include "GLFWWindow.h"
#include "Meander/Input/Input.h"
#include <GLFW/glfw3.h>

namespace Meander
{
	void GLFWWindow::Initialize(const WindowProperties& properties)
	{
		s_Properties = properties;

		MN_INFO("Initializing GLFW...");
		int status = glfwInit();
		MN_ASSERT(status, "Unable to initialize GLFW.");

		MN_INFO("Creating GLFW window...");
		m_NativeWindow = glfwCreateWindow(properties.Width, properties.Height, properties.Title, nullptr, nullptr);

		if (m_NativeWindow == nullptr)
		{
			MN_ASSERT(false, "Unable to create GLFW window.");
			glfwTerminate();
			return;
		}

		glfwSetWindowUserPointer(m_NativeWindow, this);
		glfwMakeContextCurrent(m_NativeWindow);

		glfwSetErrorCallback([](int error, const char* description)
		{
			MN_ERROR("GLFW: %s\n", description);
		});

		glfwSetKeyCallback(m_NativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			GLFWWindow* wnd = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

			if (wnd != nullptr && wnd->m_KeyCallback)
				wnd->m_KeyCallback((Key)key, (InputAction)action);
		});
		
		glfwSetMouseButtonCallback(m_NativeWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			GLFWWindow* wnd = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

			if (wnd != nullptr && wnd->m_MouseButtonCallback)
				wnd->m_MouseButtonCallback((MouseButton)button, (InputAction)action);
		});
		
		glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow* window, double xpos, double ypos)
		{
			GLFWWindow* wnd = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

		    if (wnd != nullptr && wnd->m_CursorPositionCallback)
    			wnd->m_CursorPositionCallback(xpos, ypos);
		});
		
		glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* const window, int width, int height)
		{
			GLFWWindow* wnd = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

			if (wnd != nullptr && wnd->m_ResizeCallback)
				wnd->m_ResizeCallback((uint32_t)width, (uint32_t)height);
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

	void GLFWWindow::Resize(uint32_t width, uint32_t height)
	{
		s_Properties.Width = width;
		s_Properties.Height = height;

		if (m_ResizeCallback != nullptr)
			m_ResizeCallback(width, height);
	}
}
