#include "pch.h"
#include "Sandbox.h"
#include "Meander/Window.h"
#include "Meander/Input/Input.h"
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

		camera.SetPosition({ 0.f, 2.f, -5.f });
	}

	void Sandbox::Update(GameTime& gameTime)
	{
		if (Input::IsKeyPressed(Key::Escape))
			Exit();

		const float elapsed = gameTime.GetElapsedSeconds();
		camera.SetPosition({ sin(elapsed * 2.f) * 2.f, 1.f, cos(elapsed * 2.f) * 2.f });
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