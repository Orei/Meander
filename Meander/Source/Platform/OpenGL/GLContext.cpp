#include "pch.h"
#include "GLContext.h"
#include "GLTypes.h"
#include "Meander/Window.h"
#include "Meander/Graphics/VertexArray.h"
#include <glad/glad.h>

namespace Meander
{
	void GLContext::Initialize()
	{
		MN_INFO("Creating GLAD context...");

		int status = gladLoadGL();
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
		glClear(GLTypes::GetClearFlags(flags));
	}

	void GLContext::Render(const VertexArray* vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		vertexArray->Unbind();
	}

	void GLContext::FillScreen()
	{
		glBindVertexArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}

	void GLContext::SetDepthTest(bool enabled)
	{
		if (enabled)
			Enable(GL_DEPTH_TEST);
		else
			Disable(GL_DEPTH_TEST);
	}

	void GLContext::SetBlend(bool enabled)
	{
		if (enabled)
			Enable(GL_BLEND);
		else
			Disable(GL_BLEND);
	}

	void GLContext::SetCullFace(bool enabled)
	{
		if (enabled)
			Enable(GL_CULL_FACE);
		else
			Disable(GL_CULL_FACE);
	}

	void GLContext::SetWindingOrder(const WindingOrder& order)
	{
		glFrontFace(GLTypes::GetWindingOrder(order));
	}

	void GLContext::SetCullDirection(const CullDirection& direction)
	{
		glCullFace(GLTypes::GetCullDirection(direction));
	}
}