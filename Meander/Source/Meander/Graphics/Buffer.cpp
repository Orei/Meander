#include "pch.h"
#include "Buffer.h"
#include "Context.h"
#include "Platform/OpenGL/GLBuffer.h"

namespace Meander
{
	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return new GLVertexBuffer(vertices, size);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return new GLIndexBuffer(indices, count);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}