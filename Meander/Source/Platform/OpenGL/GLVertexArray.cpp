#include "pch.h"
#include "GLVertexArray.h"
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

	GLVertexArray::GLVertexArray()
	{
		glCreateVertexArrays(1, &m_Handle);
	}

	GLVertexArray::~GLVertexArray()
	{
		glDeleteVertexArrays(1, &m_Handle);
	}

	void GLVertexArray::Bind() const
	{
		glBindVertexArray(m_Handle);
	}

	void GLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void GLVertexArray::AddVertexBuffer(VertexBuffer* buffer)
	{
		MN_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex buffer contains no layout.");

		Bind();
		buffer->Bind();

		const BufferLayout layout = buffer->GetLayout();
		for (const BufferElement& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				GetBufferDataComponents(element.Type),
				BufferTypeToOpenGL(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(buffer);

		buffer->Unbind();
		Unbind();
	}

	void GLVertexArray::SetIndexBuffer(IndexBuffer* buffer)
	{
		Bind();
		buffer->Bind();
		m_IndexBuffer = buffer;
		Unbind();
	}
}