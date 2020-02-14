#pragma once
#include "Meander/Graphics/VertexArray.h"
#include <glad/glad.h>

namespace Meander
{
	class GLVertexArray : public VertexArray
	{
	public:
		GLVertexArray();
		virtual ~GLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(VertexBuffer* buffer) override;
		virtual void SetIndexBuffer(IndexBuffer* buffer) override;

		virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const override
		{
			return m_VertexBuffers;
		}

		virtual IndexBuffer* GetIndexBuffer() const override
		{
			return m_IndexBuffer;
		}

	private:
		unsigned int m_Handle = 0;
		unsigned int m_VertexBufferIndex = 0;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer = nullptr;
	};
}