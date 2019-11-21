#include "pch.h"
#include "Sandbox/Sandbox.h"

int main()
{
	auto app = Meander::CreateApplication();
	app->Run();
	delete app;

	return 0;
}