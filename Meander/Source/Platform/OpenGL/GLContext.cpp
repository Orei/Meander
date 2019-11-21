#include "pch.h"
#include "GLContext.h"
#include "Meander/Window.h"
#include <glad/glad.h>

namespace Meander
{
	void GLContext::Initialize()
	{
		MN_INFO("Creating GLAD context...");

		int status = gladLoadGLLoader((GLADloadproc)Window::Get()->GetProcessAddress());

		if (status != GL_TRUE)
		{
			MN_CRITICAL("Unable to initialize GLAD.");
			return;
		}

		MN_INFO("OpenGL {0}", glGetString(GL_VERSION));
		MN_INFO("Renderer: {0}", glGetString(GL_RENDERER));
	}

	void GLContext::Clear()
	{
	}
}