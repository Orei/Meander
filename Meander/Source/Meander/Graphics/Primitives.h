#pragma once
#include "Meander/Common.h"
#include "Meander/Graphics/Mesh.h"

namespace Meander
{
	class Primitives
	{
	public:
		static void Initialize()
		{
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
				// Front 
				0, 1, 2, 0, 2, 3,
				// Back
				4, 5, 6, 4, 6, 7,
				// Right
				8, 9, 10, 8, 10, 11,
				// Left
				12, 13, 14,	12, 14, 15,
				// Top
				16, 17, 18, 16, 18, 19,
				// Bottom
				20, 21, 22, 20, 22, 23
			};

			m_Quad.reset(new Mesh(quadVertices, sizeof(quadVertices), quadIndices, sizeof(quadIndices),
				{
					{ "a_Position", BufferDataType::Float3 },
					{ "a_Normal", BufferDataType::Float3 },
					{ "a_UV", BufferDataType::Float2 }
				}));

			m_Cube.reset(new Mesh(cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices),
				{
					{ "a_Position", BufferDataType::Float3 },
					{ "a_Normal", BufferDataType::Float3 },
					{ "a_UV", BufferDataType::Float2 }
				}));
		}

		static const Shared<Mesh>& GetQuad() { return m_Quad; }
		static const Shared<Mesh>& GetCube() { return m_Cube; }

	private:
		static Shared<Mesh> m_Quad;
		static Shared<Mesh> m_Cube;
	};
}