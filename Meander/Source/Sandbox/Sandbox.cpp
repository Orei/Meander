#include "pch.h"
#include "Sandbox.h"
#include "Meander/Window.h"
#include "Meander/Graphics/Context.h"
#include "Meander/Graphics/Buffer.h"
#include "Meander/Graphics/VertexArray.h"
#include "Meander/Graphics/Mesh.h"

namespace Meander
{
	Shared<Mesh> mesh;

	void Sandbox::Initialize()
	{
		m_Context->SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
	}

	void Sandbox::Load()
	{
		float squareVertices[5 * 4] = 
		{
			-0.5f, -0.5f,	0.0f, 0.0f,
			 0.5f, -0.5f,	1.0f, 0.0f,
			 0.5f,  0.5f,	1.0f, 1.0f,
			-0.5f,  0.5f,	0.0f, 1.0f
		};
		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		mesh.reset(new Mesh(squareVertices, sizeof(squareVertices), squareIndices, sizeof(squareIndices), 
			{
				{ "a_Position", BufferDataType::Float2 },
				{ "a_UV", BufferDataType::Float2 }
			}));
	}

	void Sandbox::Update(float deltaTime)
	{
	}

	void Sandbox::Render()
	{
		m_Context->Clear(ClearFlags::Color | ClearFlags::Depth);
		m_Context->Render(mesh->GetVertexArray());
	}
}