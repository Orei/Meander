#include "pch.h"
#include "Application.h"
#include "Utility/Log.h"

namespace Meander
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		Log::Initialize();
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

		while (m_Running)
		{
			Update(0.f);
			Render();
		}
	}

	void Application::Exit() 
	{
		m_Running = false;
	}
}