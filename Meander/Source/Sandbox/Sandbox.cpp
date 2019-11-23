#include "pch.h"
#include "Sandbox.h"
#include "Meander/Window.h"
#include "Meander/Graphics/Context.h"
#include "Meander/Graphics/Buffer.h"
#include "Meander/Graphics/VertexArray.h"
#include "Meander/Graphics/Mesh.h"
#include "Meander/Graphics/Shader.h"
#include "Meander/Graphics/Camera.h"

namespace Meander
{
	Shared<Shader> shader;
	Shared<Mesh> mesh;
	Transform meshTransform;
	PerspectiveCamera camera(70.f, (float)1280 / 720);

	void Sandbox::Initialize()
	{
		m_Context->SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
	}

	void Sandbox::Load()
	{
		/* Load shader */
		shader = Shader::Create("Assets/Shaders/Test.glsl");

		/* Create mesh */
		float squareVertices[] = 
		{
			-0.5f, -0.5f, 0.0f,	  0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,	  1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,	  1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,	  0.0f, 1.0f
		};
		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		mesh.reset(new Mesh(squareVertices, sizeof(squareVertices), squareIndices, sizeof(squareIndices), 
			{
				{ "a_Position", BufferDataType::Float3 },
				{ "a_UV", BufferDataType::Float2 }
			}));
	}

	void Sandbox::Update(float deltaTime)
	{
		static float time = 0.f;
		time += deltaTime / 1000.f;

		camera.SetPosition({ sin(time) * 2.f, 1.f, cos(time) * 2.f });
	}

	void Sandbox::Render()
	{
		m_Context->Clear(ClearFlags::Color | ClearFlags::Depth);

		shader->Set("u_Projection", camera.GetProjectionMatrix());
		shader->Set("u_View", camera.GetViewMatrix());
		shader->Set("u_Transform", meshTransform.GetMatrix());

		shader->Bind();
		m_Context->Render(mesh->GetVertexArray());
		shader->Unbind();
	}
}