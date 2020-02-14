#pragma once
#include "Buffer.h"

namespace Meander
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(VertexBuffer* buffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* buffer) = 0;

		virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const = 0;
		virtual IndexBuffer* GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}