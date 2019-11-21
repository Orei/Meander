#include "pch.h"
#include "Sandbox/Sandbox.h"
#include "Platform/GLFW/GLFWWindow.h"
#include "Platform/OpenGL/GLContext.h"

namespace Meander
{
	Application* CreateApplication()
	{
		return new Sandbox();
	}

	Window* CreateWindow()
	{
		return new GLFWWindow();
	}

	Context* CreateContext()
	{
		return new GLContext();
	}
}

int main()
{
	auto app = Meander::CreateApplication();
	app->Run();
	delete app;

	return 0;
}