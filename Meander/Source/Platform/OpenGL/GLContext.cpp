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

	void GLContext::Enable(unsigned int capabilities)
	{
		glEnable(capabilities);
	}

	void GLContext::Disable(unsigned int capabilities)
	{
		glDisable(capabilities);
	}

	void GLContext::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLContext::Clear(ClearFlags flags)
	{
		glClear((int)flags);
	}
}