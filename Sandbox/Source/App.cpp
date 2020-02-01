#include "App.h"
#include <Meander/Meander.h>

namespace Sandbox
{
	using namespace Meander;

	void App::Initialize()
	{
	}

	void App::Load()
	{
	}

	void App::Update(GameTime& gameTime)
	{
	}

	void App::Render()
	{
		Renderer::Begin();
		Renderer::Clear(ClearFlags::Color | ClearFlags::Depth);
		Renderer::End();
	}
}

Meander::Application* Meander::CreateApplication()
{
	return new Sandbox::App();
}

int main()
{
	auto app = Meander::CreateApplication();
	app->Run();
	delete app;
	return 0;
}