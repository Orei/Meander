#include "pch.h"
#include "Meander/Application.h"

int main()
{
	auto app = Meander::Application::Create();
	app->Run();
	delete app;

	return 0;
}