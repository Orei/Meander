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

		virtual void AddVertexBuffer(const Shared<VertexBuffer>& buffer) override;
		virtual void SetIndexBuffer(const Shared<IndexBuffer>& buffer) override;

		virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const override
		{
			return m_VertexBuffers;
		}

		virtual const Shared<IndexBuffer>& GetIndexBuffer() const override
		{
			return m_IndexBuffer;
		}

	private:
		unsigned int m_Handle = 0;
		unsigned int m_VertexBufferIndex = 0;
		std::vector<Shared<VertexBuffer>> m_VertexBuffers;
		Shared<IndexBuffer> m_IndexBuffer = nullptr;
	};
}