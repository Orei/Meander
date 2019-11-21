#include "pch.h"
#include "Application.h"

namespace Meander
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
	}
	
	Application::~Application()
	{
	}

	void Application::Run()
	{
		m_Running = true;

		while (m_Running)
		{
		}
	}

	void Application::Exit() 
	{
		m_Running = false;
	}
}