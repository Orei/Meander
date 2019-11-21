#include "pch.h"
#include "Sandbox.h"
#include "Meander/Window.h"

namespace Meander
{
	void Sandbox::Initialize()
	{
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
		m_Window->Present();
	}
}