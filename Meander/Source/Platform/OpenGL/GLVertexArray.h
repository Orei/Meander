#pragma once
#include "Meander/Graphics/VertexArray.h"
#include <glad/glad.h>

namespace Meander
{
	static GLenum BufferTypeToOpenGL(const BufferDataType& type)
	{
		switch (type)
		{
		case BufferDataType::Float:
		case BufferDataType::Float2:
		case BufferDataType::Float3:
		case BufferDataType::Float4:
		case BufferDataType::Mat3:
		case BufferDataType::Mat4:
			return GL_FLOAT;
		case BufferDataType::Int:
		case BufferDataType::Int2:
		case BufferDataType::Int3:
		case BufferDataType::Int4:
			return GL_INT;
		case BufferDataType::Bool:
			return GL_BOOL;
		}

		MN_ASSERT(false, "Unhandled BufferDataType.");
		return 0;
	}

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