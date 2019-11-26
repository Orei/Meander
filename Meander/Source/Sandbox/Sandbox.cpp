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
	Shared<Shader> testShader;
	Shared<Mesh> mesh;
	Transform meshTransform;
	PerspectiveCamera camera(70.f, (float)1280 / 720);

	void Sandbox::Initialize()
	{
		m_Context->SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
		m_Context->SetDepthTest(true);
		m_Window->SetCursorState(false);
	}

	void Sandbox::Load()
	{
		/* Load shader */
		testShader = Shader::Create("Assets/Shaders/Test.glsl");

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

		camera.GetTransform().Translate(WORLD_FORWARD * -5.f);
	}

	void Sandbox::Update(GameTime& gameTime)
	{
		if (Input::IsKeyPressed(Key::Escape))
			Exit();

		glm::quat rotation = glm::angleAxis(glm::radians(45.f * gameTime.GetDeltaSeconds()), meshTransform.GetUp() * Input::GetKeysAxis(Key::Left, Key::Right)) *
			glm::angleAxis(glm::radians(45.f * gameTime.GetDeltaSeconds()), meshTransform.GetRight() * Input::GetKeysAxis(Key::Down, Key::Up));

		meshTransform.Rotate(rotation);

		glm::vec3 movement = Input::GetKeysAxis(Key::A, Key::D) * camera.GetTransform().GetRight() +
			Input::GetKeysAxis(Key::LeftControl, Key::Space) * WORLD_UP +
			Input::GetKeysAxis(Key::S, Key::W) * camera.GetTransform().GetForward();

		camera.GetTransform().Translate(movement * gameTime.GetDeltaSeconds() * 4.f);

		glm::vec2 look = Input::GetMouseDelta() * 0.05f;
		camera.GetTransform().SetRotation(camera.GetTransform().GetRotation() * glm::angleAxis(glm::radians(look.x), WORLD_UP));
		camera.GetTransform().SetRotation(glm::angleAxis(glm::radians(look.y), WORLD_RIGHT) * camera.GetTransform().GetRotation());
	}

	void Sandbox::Render()
	{
		m_Context->Clear(ClearFlags::Color | ClearFlags::Depth);

		testShader->Set("u_Projection", camera.GetProjectionMatrix());
		testShader->Set("u_View", camera.GetViewMatrix());
		testShader->Set("u_Transform", meshTransform.GetMatrix());

		testShader->Bind();
		m_Context->Render(mesh->GetVertexArray());
		testShader->Unbind();
	}
}