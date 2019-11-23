#pragma once
#include "Meander/Graphics/Buffer.h"

namespace Meander
{
	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(float* vertices, unsigned int size);
		virtual ~GLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override 
		{
			m_Layout = layout;
		}

		virtual const BufferLayout& GetLayout() const override 
		{
			return m_Layout;
		}

	private:
		unsigned int m_Handle = 0;
		BufferLayout m_Layout;
	};

	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(unsigned int* indices, unsigned int count);
		virtual ~GLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual unsigned int GetCount() const override
		{
			return m_Count;
		}

	private:
		unsigned int m_Handle = 0;
		unsigned int m_Count = 0;
	};
}