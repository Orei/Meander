#pragma once
#include "Meander/Graphics/Buffer.h"

namespace Meander
{
	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(float* vertices, uint32_t size);
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
		uint32_t m_Handle = 0;
		BufferLayout m_Layout;
	};

	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~GLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override
		{
			return m_Count;
		}

	private:
		uint32_t m_Handle = 0;
		uint32_t m_Count = 0;
	};
}