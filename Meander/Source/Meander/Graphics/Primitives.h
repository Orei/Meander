#pragma once
#include "Meander/Common.h"
#include "Meander/Graphics/Mesh.h"
#include <iostream>

namespace Meander
{
	class Primitives
	{
	public:
		static void Initialize()
		{
			/* NOTE: All of the generated primitives must match this layout. */
			m_Layout = 
			{
				{ "a_Position", BufferDataType::Float3 },
				{ "a_Normal", BufferDataType::Float3 },
				{ "a_UV", BufferDataType::Float2 }
			};

			float quadVertices[] =
			{
				-0.5f, -0.5f, 0.f,   0.f, 0.f, 1.f,   0.0f, 0.0f,
				 0.5f, -0.5f, 0.f,   0.f, 0.f, 1.f,   1.0f, 0.0f,
				 0.5f,  0.5f, 0.f,   0.f, 0.f, 1.f,   1.0f, 1.0f,
				-0.5f,  0.5f, 0.f,   0.f, 0.f, 1.f,   0.0f, 1.0f
			};

			unsigned int quadIndices[] =
			{
				0, 1, 2, 0, 2, 3
			};

			float cubeVertices[] =
			{
				-0.5f, -0.5f,  0.5f,    0.f,  0.f,  1.f,    0.0f, 0.0f, // Front face
				 0.5f, -0.5f,  0.5f,    0.f,  0.f,  1.f,    1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,    0.f,  0.f,  1.f,    1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,    0.f,  0.f,  1.f,    0.0f, 1.0f,

				 0.5f, -0.5f, -0.5f,    0.f,  0.f, -1.f,    0.0f, 0.0f, // Back face
				-0.5f, -0.5f, -0.5f,    0.f,  0.f, -1.f,    1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,    0.f,  0.f, -1.f,    1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,    0.f,  0.f, -1.f,    0.0f, 1.0f,

				 0.5f, -0.5f,  0.5f,    1.f,  0.f,  0.f,    0.0f, 0.0f, // Right face
				 0.5f, -0.5f, -0.5f,    1.f,  0.f,  0.f,    1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,    1.f,  0.f,  0.f,    1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,    1.f,  0.f,  0.f,    0.0f, 1.0f,

				-0.5f, -0.5f, -0.5f,   -1.f,  0.f,  0.f,    0.0f, 0.0f, // Left face
				-0.5f, -0.5f,  0.5f,   -1.f,  0.f,  0.f,    1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,   -1.f,  0.f,  0.f,    1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,   -1.f,  0.f,  0.f,    0.0f, 1.0f,

				-0.5f,  0.5f,  0.5f,    0.f,  1.f,  0.f,    0.0f, 0.0f, // Top face
				 0.5f,  0.5f,  0.5f,    0.f,  1.f,  0.f,    1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,    0.f,  1.f,  0.f,    1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,    0.f,  1.f,  0.f,    0.0f, 1.0f,

				 0.5f, -0.5f,  0.5f,    0.f, -1.f,  0.f,    0.0f, 0.0f, // Bottom face
				-0.5f, -0.5f,  0.5f,    0.f, -1.f,  0.f,    1.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,    0.f, -1.f,  0.f,    1.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,    0.f, -1.f,  0.f,    0.0f, 1.0f,
			};

			unsigned int cubeIndices[] =
			{
				0, 1, 2, 0, 2, 3, // Front 
				4, 5, 6, 4, 6, 7, // Back
				8, 9, 10, 8, 10, 11, // Right
				12, 13, 14,	12, 14, 15, // Left
				16, 17, 18, 16, 18, 19, // Top
				20, 21, 22, 20, 22, 23 // Bottom
			};

			m_Quad.reset(new Mesh(quadVertices, sizeof(quadVertices), 
				quadIndices, sizeof(quadIndices) / sizeof(unsigned int),
				m_Layout));

			m_Cube.reset(new Mesh(cubeVertices, sizeof(cubeVertices), 
				cubeIndices, sizeof(cubeIndices) / sizeof(unsigned int), 
				m_Layout));

			GeneratePlane(10, 10, m_Plane);
		}

		static void GeneratePlane(int rows, int columns, Shared<Mesh>& mesh)
		{
			// TODO: Store this elsewhere for the entire class, this is a copy of the initializer quad
			float quadVertices[] =
			{
				-0.5f, -0.5f, 0.f,   0.f, 0.f, 1.f,   0.0f, 0.0f,
				 0.5f, -0.5f, 0.f,   0.f, 0.f, 1.f,   1.0f, 0.0f,
				 0.5f,  0.5f, 0.f,   0.f, 0.f, 1.f,   1.0f, 1.0f,
				-0.5f,  0.5f, 0.f,   0.f, 0.f, 1.f,   0.0f, 1.0f
			};

			unsigned int quadIndices[] =
			{
				0, 1, 2, 0, 2, 3
			};

			std::vector<float> vertices;
			std::vector<unsigned int> indices;

			float halfRows = (float)rows / 2.f;
			float halfColumns = (float)columns / 2.f;

			for (int y = 0; y < columns; ++y)
			{
				for (int x = 0; x < rows; ++x)
				{
					// There are 4 vertices per quad
					for (int vertexIndex = 0; vertexIndex < 4; ++vertexIndex)
					{
						// Multiply by number of components per vertex
						int index = vertexIndex * 8;

						// Position
						float px = quadVertices[index] + x - halfRows + 0.5f;
						float py = quadVertices[index + 1] + y - halfColumns + 0.5f;
						float pz = quadVertices[index + 2];

						// Normal
						float nx = quadVertices[index + 3];
						float ny = quadVertices[index + 4];
						float nz = quadVertices[index + 5];

						// UV
						float ux = quadVertices[index + 6];
						float uy = quadVertices[index + 7];

						vertices.push_back(px);
						vertices.push_back(py);
						vertices.push_back(pz);

						vertices.push_back(nx);
						vertices.push_back(ny);
						vertices.push_back(nz);

						vertices.push_back(ux);
						vertices.push_back(uy);
					}

					// Copy quad indices and offset
					for (int i = 0; i < 6; ++i)
					{
						indices.push_back(quadIndices[i] + (x + y * rows) * 4);
					}
				}
			}

			// We want the size of the vertex array, but only the the number of indices
			unsigned int vertexSize = (unsigned int)vertices.size() * sizeof(float);
			unsigned int indexCount = (unsigned int)indices.size();

			mesh.reset(new Mesh(&vertices[0], vertexSize, 
				&indices[0], indexCount, 
				m_Layout));
		}

		static const Shared<Mesh>& GetQuad() { return m_Quad; }
		static const Shared<Mesh>& GetCube() { return m_Cube; }
		static const Shared<Mesh>& GetPlane() { return m_Plane; }

	private:
		static Shared<Mesh> m_Quad;
		static Shared<Mesh> m_Cube;
		static Shared<Mesh> m_Plane;
		static BufferLayout m_Layout;
	};
}