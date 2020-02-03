#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "GameTime.h"
#include "Graphics/Context.h"
#include "Graphics/Primitives.h"
#include "Input/Input.h"
#include "Platform/OpenGL/GLContext.h"
#include "Platform/GLFW/GLFWWindow.h"
#include "ImGui/ImGuiRenderer.h"

namespace Meander
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		MN_ASSERT(s_Instance == nullptr, "An instance of Application already exists.");
		s_Instance = this;

		// Has to be created first to error messages
		Log::Initialize();

		// Create window and graphics context
		m_Window = new GLFWWindow();
		m_Context = new GLContext();

		// TODO: Allow the client application to modify properties
		m_Window->Initialize(WindowProperties());
		m_Context->Initialize();

		// Created after the context
		Primitives::Initialize();
		ImGuiRenderer::Initialize();
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
		gameTime.Start();
		while (m_Running && !m_Window->IsClosing())
		{
			gameTime.Update();

			Update(gameTime);
			Render(gameTime);

			ImGuiRenderer::Begin();
			OnGui(gameTime);
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