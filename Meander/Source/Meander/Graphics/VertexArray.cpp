#include "pch.h"
#include "VertexArray.h"
#include "Context.h"
#include "Platform/OpenGL/GLVertexArray.h"

namespace Meander
{
	VertexArray* VertexArray::Create()
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return new GLVertexArray();
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}