#include "pch.h"
#include "FrameBuffer.h"
#include "Context.h"
#include "Platform/OpenGL/GLFrameBuffer.h"

namespace Meander
{
	FrameBuffer* FrameBuffer::Create(unsigned int width, unsigned int height)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case Context::OpenGL:
			return new GLFrameBuffer(width, height);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}