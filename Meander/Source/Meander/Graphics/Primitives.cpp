#include "pch.h"
#include "Primitives.h"
#include "Meander/Graphics/Mesh.h"

namespace Meander
{
	Mesh* Primitives::s_Quad = nullptr;
	Mesh* Primitives::s_Cube = nullptr;
	Mesh* Primitives::s_Plane = nullptr;

	// NOTE: All of the generated meshes must match this layout.
	BufferLayout Primitives::s_Layout = 
	{
		{ "a_Position", BufferDataType::Float3 },
		{ "a_Normal", BufferDataType::Float3 },
		{ "a_UV", BufferDataType::Float2 }
	};

	static float s_QuadVertices[] =
	{
		-0.5f, -0.5f, 0.f,   0.f, 0.f, 1.f,   0.0f, 0.0f,
		0.5f, -0.5f, 0.f,   0.f, 0.f, 1.f,   1.0f, 0.0f,
		0.5f,  0.5f, 0.f,   0.f, 0.f, 1.f,   1.0f, 1.0f,
		-0.5f,  0.5f, 0.f,   0.f, 0.f, 1.f,   0.0f, 1.0f
	};

	unsigned int s_QuadIndices[] =
	{
		0, 1, 2, 0, 2, 3
	};

	float s_CubeVertices[] =
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

	unsigned int s_CubeIndices[] =
	{
		0, 1, 2, 0, 2, 3, // Front 
		4, 5, 6, 4, 6, 7, // Back
		8, 9, 10, 8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Top
		20, 21, 22, 20, 22, 23 // Bottom
	};

	void Primitives::Initialize()
	{
		s_Quad = new Mesh(s_QuadVertices, sizeof(s_QuadVertices),
			s_QuadIndices, sizeof(s_QuadIndices) / sizeof(unsigned int),
			s_Layout);

		s_Cube = new Mesh(s_CubeVertices, sizeof(s_CubeVertices),
			s_CubeIndices, sizeof(s_CubeIndices) / sizeof(unsigned int),
			s_Layout);

		s_Plane = GeneratePlane(10, 10);
	}

	Mesh* Primitives::GeneratePlane(int rows, int columns)
	{
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
					float px = s_QuadVertices[index] + x - halfRows + 0.5f;
					float py = s_QuadVertices[index + 1] + y - halfColumns + 0.5f;
					float pz = s_QuadVertices[index + 2];

					// Normal
					float nx = s_QuadVertices[index + 3];
					float ny = s_QuadVertices[index + 4];
					float nz = s_QuadVertices[index + 5];

					// UV
					float ux = s_QuadVertices[index + 6];
					float uy = s_QuadVertices[index + 7];

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
					indices.push_back(s_QuadIndices[i] + (x + y * rows) * 4);
				}
			}
		}

		// We want the size of the vertex array, but only the the number of indices
		unsigned int vertexSize = (unsigned int)vertices.size() * sizeof(float);
		unsigned int indexCount = (unsigned int)indices.size();

		// Create mesh and return
		return new Mesh(&vertices[0], vertexSize,
			&indices[0], indexCount,
			s_Layout);
	}
}