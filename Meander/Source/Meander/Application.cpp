#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "GameTime.h"
#include "Graphics/Primitives.h"
#include "Input/Input.h"
#include "Platform/OpenGL/GLContext.h"
#include "Platform/GLFW/GLFWWindow.h"
#include "ImGui/ImGuiRenderer.h"

namespace Meander
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const WindowProperties& windowProperties)
	{
		MN_ASSERT(s_Instance == nullptr, "An instance of Application already exists.");
		s_Instance = this;

		// Has to be created first to log messages
		Log::Initialize();

		// Create window and graphics context
		m_Window = new GLFWWindow();
		m_RenderContext = new GLContext();

		m_Window->Initialize(windowProperties);
		m_RenderContext->Initialize();

		// Initialize after context
		Primitives::Initialize();
		ImGuiRenderer::Initialize();
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	void Application::Run(Client* context)
	{
		m_Running = true;

		context->Initialize_Internal(this, m_RenderContext, m_Window);
		context->Initialize();
		context->Load();

		GameTime gameTime;
		gameTime.Start();
		while (m_Running && !m_Window->IsClosing())
		{
			gameTime.Update();

			context->Update(gameTime);
			context->Render(gameTime);

			ImGuiRenderer::Begin();
			context->RenderUI(gameTime);
			ImGuiRenderer::End();

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