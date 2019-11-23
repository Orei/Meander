#include "pch.h"
#include "GLBuffer.h"
#include "GLContext.h"
#include <glad/glad.h>

namespace Meander
{
	/* Vertex Buffer */
	GLVertexBuffer::GLVertexBuffer(float* vertices, unsigned int size)
	{
		glCreateBuffers(1, &m_Handle);
		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &m_Handle);
	}

	void GLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
	}

	void GLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/* Index Buffer */
	GLIndexBuffer::GLIndexBuffer(unsigned int* indices, unsigned int count)
		: m_Count(count / sizeof(unsigned int))
	{
		glCreateBuffers(1, &m_Handle);
		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
		glBufferData(GL_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &m_Handle);
	}

	void GLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
	}

	void GLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}