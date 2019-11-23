#include "pch.h"
#include "GLVertexArray.h"
#include <glad/glad.h>

namespace Meander
{
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

	void GLVertexArray::AddVertexBuffer(const Shared<VertexBuffer>& buffer)
	{
		MN_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		Bind();
		buffer->Bind();

		const auto& layout = buffer->GetLayout();
		for (const auto& element : layout)
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

	void GLVertexArray::SetIndexBuffer(const Shared<IndexBuffer>& buffer)
	{
		Bind();
		buffer->Bind();
		m_IndexBuffer = buffer;
		Unbind();
	}
}