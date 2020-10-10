#include "pch.h"
#include "Buffer.h"
#include "RenderContext.h"
#include "Platform/OpenGL/GLBuffer.h"

namespace Meander
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RenderContext::Get()->GetContextAPI())
		{
		case RenderContextAPI::OpenGL:
			return new GLVertexBuffer(vertices, size);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (RenderContext::Get()->GetContextAPI())
		{
		case RenderContextAPI::OpenGL:
			return new GLIndexBuffer(indices, count);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}