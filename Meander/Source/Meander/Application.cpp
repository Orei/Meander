#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "GameTime.h"
#include "Graphics/Context.h"
#include "Graphics/Primitives.h"
#include "Input/Input.h"
#include "Utility/Timer.h"

#ifdef _WIN32
#include "Platform/OpenGL/GLContext.h"
#include "Platform/GLFW/GLFWWindow.h"
#endif

namespace Meander
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		MN_ASSERT(s_Instance == nullptr, "An instance of Application already exists.");
		s_Instance = this;

		// Has to be created first to error messages
		Log::Initialize();

#ifdef _WIN32
		// Create window and graphics context
		m_Window = new GLFWWindow();
		m_Context = new GLContext();
#else
		MN_ASSERT(false, "Meander doesn't support this operating system.");
#endif

		// TODO: Allow the client application to modify properties
		m_Window->Initialize(WindowProperties());
		m_Context->Initialize();

		// Created after the context
		Primitives::Initialize();
	}
	
	Application::~Application()
	{
		s_Instance = nullptr;
	}

	void Application::Run()
	{
		m_Running = true;

		Initialize();
		Load();

		GameTime gameTime;

		// Avoid huge initial timestep
		Timer timer;
		timer.Start();

		while (m_Running && !m_Window->IsClosing())
		{
			timer.Stop();
			gameTime.Update((float)timer.GetElapsed() / 1000.f);
			timer.Start();

			Update(gameTime);
			Render();

			Input::Update();
			m_Window->Present();
			m_Window->PollEvents();
		}
	}

	void Application::Exit() 
	{
		m_Running = false;
	}
}