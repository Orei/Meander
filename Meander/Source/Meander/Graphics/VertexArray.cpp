#include "pch.h"
#include "VertexArray.h"
#include "RenderContext.h"
#include "Platform/OpenGL/GLVertexArray.h"

namespace Meander
{
	VertexArray* VertexArray::Create()
	{
		switch (RenderContext::Get()->GetContextAPI())
		{
		case RenderContextAPI::OpenGL:
			return new GLVertexArray();
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}