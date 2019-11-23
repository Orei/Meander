#include "pch.h"
#include "Buffer.h"
#include "Context.h"
#include "Platform/OpenGL/GLBuffer.h"

namespace Meander
{
	Shared<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return CreateShared<GLVertexBuffer>(vertices, size);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}

	Shared<IndexBuffer> IndexBuffer::Create(unsigned int* vertices, unsigned int count)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return CreateShared<GLIndexBuffer>(vertices, count);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}