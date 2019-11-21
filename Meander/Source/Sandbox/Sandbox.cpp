#include "pch.h"
#include "Sandbox.h"
#include "Meander/Window.h"
#include "Meander/Graphics/Context.h"

namespace Meander
{
	void Sandbox::Initialize()
	{
		m_Context->SetClearColor(glm::vec4(0.4f, 0.2f, 0.6f, 1.f));
	}

	void Sandbox::Load()
	{
	}

	void Sandbox::Update(float deltaTime)
	{
		m_Window->PollEvents();
	}

	void Sandbox::Render()
	{
		m_Context->Clear(ClearFlags::Color);
		m_Window->Present();
	}
}