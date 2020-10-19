#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "GameTime.h"
#include "Graphics/Primitives.h"
#include "Input/Input.h"
#include "Platform/OpenGL/GLContext.h"
#include "Platform/GLFW/GLFWWindow.h"
#include "Platform/ImGui/ImCanvas.h"

namespace Meander
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const WindowProperties& windowProperties)
	{
		MN_ASSERT(s_Instance == nullptr, "An instance of Application already exists.");
		s_Instance = this;

		// Create window, render context and canvas
		m_Window = new GLFWWindow();
		m_RenderContext = new GLContext();
		m_Canvas = new ImCanvas();

		m_Window->Initialize(windowProperties);
		m_RenderContext->Initialize();
		m_Canvas->Initialize(m_Window, m_RenderContext);

		// Requires render context to be initialized
		Primitives::Initialize();
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	void Application::Run(Client* context)
	{
		m_Running = true;

		context->Initialize_Internal(this, m_RenderContext, m_Window, m_Canvas);
		context->Initialize();
		context->Load();

		GameTime gameTime;
		gameTime.Start();
		while (m_Running && !m_Window->IsClosing())
		{
			gameTime.Update();

			context->Update(gameTime);
			context->Render(gameTime);

			m_Canvas->Begin();
			context->RenderUI(gameTime);
			m_Canvas->End();

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
