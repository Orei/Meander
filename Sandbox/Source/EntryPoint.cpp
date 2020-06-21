#include "Game.h"
#include "Meander/Application.h"

int main()
{
	Meander::Application app;
	Sandbox::Game context;
	app.Run(&context);
	return 0;
}