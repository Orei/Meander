#include "pch.h"
#include "Platform/GLFW/GLFWWindow.h"

namespace Meander
{
	WindowProperties Window::s_Properties;
	Window* Window::s_Instance = nullptr;

	Window::Window()
	{
		MN_ASSERT(s_Instance == nullptr, "An instance of Window already exists.");
		s_Instance = this;
	}

	Window::~Window()
	{
		s_Instance = nullptr;
	}
}