#pragma once

namespace Meander
{
	class Mesh
	{
	public:
		Mesh(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize, const BufferLayout& layout)
		{
			m_VertexArray = VertexArray::Create();
			
			Shared<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, verticesSize);
			vertexBuffer->SetLayout(layout);

			Shared<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, indicesSize);
			m_VertexArray->AddVertexBuffer(vertexBuffer);
			m_VertexArray->SetIndexBuffer(indexBuffer);
		}

		Mesh(const Shared<VertexArray>& vertexArray)
			: m_VertexArray(vertexArray)
		{
		}

		const Shared<VertexArray>& GetVertexArray() const { return m_VertexArray; }

	private:
		Shared<VertexArray> m_VertexArray;
	};
}