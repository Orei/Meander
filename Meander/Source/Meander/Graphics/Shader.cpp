#include "pch.h"
#include "Shader.h"
#include "Context.h"
#include "Platform/OpenGL/GLShader.h"

namespace Meander
{
	Shader* Shader::Create(const char* path)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return new GLShader(path);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}