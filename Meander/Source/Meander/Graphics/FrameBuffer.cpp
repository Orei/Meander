#include "pch.h"
#include "FrameBuffer.h"
#include "RenderContext.h"
#include "Platform/OpenGL/GLFrameBuffer.h"

namespace Meander
{
	FrameBuffer* FrameBuffer::Create(unsigned int width, unsigned int height)
	{
		switch (RenderContext::Get()->GetContextAPI())
		{
		case RenderContextAPI::OpenGL:
			return new GLFrameBuffer(width, height);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}