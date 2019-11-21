#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Graphics/Context.h"
#include "Utility/Timer.h"

namespace Meander
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		MN_ASSERT(s_Instance == nullptr, "An instance of Application already exists.");

		s_Instance = this;

		Log::Initialize();
		
		// Create window and graphics context
		m_Window = CreateWindow();
		m_Context = CreateContext();

		// TODO: Allow the client application to modify properties
		m_Window->Initialize(WindowProperties());
		m_Context->Initialize();
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

		// Avoid huge initial timestep
		Timer timer;
		timer.Start();

		while (m_Running && !m_Window->IsClosing())
		{
			timer.Stop();
			const float delta = (float)timer.GetElapsed();
			timer.Start();

			Update(delta);
			Render();

			m_Window->Present();
			m_Window->PollEvents();
		}
	}

	void Application::Exit() 
	{
		m_Running = false;
	}
}