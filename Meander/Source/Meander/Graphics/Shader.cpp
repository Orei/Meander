#include "pch.h"
#include "Shader.h"
#include "RenderContext.h"
#include "Platform/OpenGL/GLShader.h"

namespace Meander
{
	Shader* Shader::Create(const char* path)
	{
		switch (RenderContext::Get()->GetContextAPI())
		{
		case RenderContextAPI::OpenGL:
			return new GLShader(path);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}