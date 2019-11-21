#include "pch.h"
#include "Sandbox.h"
#include "Meander/Utility/Log.h"

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
		MN_TRACE("Update");
	}

	void Sandbox::Render()
	{
	}

	Application* CreateApplication()
	{
		return new Sandbox();
	}
}