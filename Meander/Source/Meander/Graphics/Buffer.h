#pragma once
#include "Meander/Common.h"
#include <initializer_list>
#include <vector>

namespace Meander
{
	enum class BufferDataType
	{
		Bool = 0,
		Int,
		Int2,
		Int3,
		Int4,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
	};

	static unsigned int GetBufferDataComponents(const BufferDataType& type)
	{
		switch (type)
		{
		case BufferDataType::Bool:
		case BufferDataType::Int:
		case BufferDataType::Float:
			return 1;
		case BufferDataType::Int2:
		case BufferDataType::Float2:
			return 2;
		case BufferDataType::Int3:
		case BufferDataType::Float3:
			return 3;
		case BufferDataType::Int4:
		case BufferDataType::Float4:
			return 4;
		case BufferDataType::Mat3:
			return 3 * 3;
		case BufferDataType::Mat4:
			return 4 * 4;
		}

		MN_ASSERT(false, "Unhandled BufferDataType.");
		return 0;
	}

	static unsigned int GetBufferDataSize(const BufferDataType& type)
	{
		switch (type)
		{
			case BufferDataType::Bool:
				return sizeof(bool);
			case BufferDataType::Float:
			case BufferDataType::Float2:
			case BufferDataType::Float3:
			case BufferDataType::Float4:
				return sizeof(float) * GetBufferDataComponents(type);
			case BufferDataType::Int:
			case BufferDataType::Int2:
			case BufferDataType::Int3:
			case BufferDataType::Int4:
				return sizeof(int) * GetBufferDataComponents(type);
			case BufferDataType::Mat3:
				return 3 * GetBufferDataComponents(type);
			case BufferDataType::Mat4:
				return 4 * GetBufferDataComponents(type);
		}

		MN_ASSERT(false, "Unhandled BufferDataType.");
		return 0;
	}

	struct BufferElement
	{
		const char* Name;
		BufferDataType Type;
		unsigned int Size;
		unsigned int Offset;
		bool Normalized;

		BufferElement(const char* name, const BufferDataType& type, bool normalized = false)
			: Name(name), Type(type), Normalized(normalized), Size(GetBufferDataSize(type)), Offset(0)
		{
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() { }
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

		void CalculateOffsetAndStride()
		{
			m_Stride = 0;
			
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* vertices, uint32_t count);
	};
}