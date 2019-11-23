#include "pch.h"
#include "GLContext.h"
#include "Meander/Window.h"
#include "Meander/Graphics/VertexArray.h"
#include <glad/glad.h>

namespace Meander
{
	void GLContext::Initialize()
	{
		MN_INFO("Creating GLAD context...");

		int status = gladLoadGLLoader((GLADloadproc)Window::Get()->GetProcessAddress());

		MN_ASSERT(status, "Unable to initialize GLAD.");

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

	void GLContext::Clear(const ClearFlags& flags)
	{
		glClear((int)flags);
	}

	void GLContext::Render(const Shared<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		vertexArray->Unbind();
	}
}