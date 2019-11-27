#include "pch.h"
#include "Sandbox.h"
#include "Meander/Window.h"
#include "Meander/Input/Input.h"
#include "Meander/Graphics/Context.h"
#include "Meander/Graphics/Mesh.h"
#include "Meander/Graphics/Shader.h"
#include "Meander/Graphics/Camera.h"
#include "Meander/Graphics/Texture.h"
#include "Meander/Graphics/Material.h"
#include "Meander/Graphics/Primitives.h"

namespace Meander
{
	Material testMaterial;
	Transform meshTransform;
	PerspectiveCamera camera(70.f, (float)1280 / 720);

	void Sandbox::Initialize()
	{
		m_Window->SetCursorState(false);
		m_Context->SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
		m_Context->SetDepthTest(true);
		m_Context->SetBlend(true);
		m_Context->SetCullFace(true);
		m_Context->SetWindingOrder(WindingOrder::CounterClockwise);
		m_Context->SetCullDirection(CullDirection::Back);

		// Move the camera back, so we can see the center
		camera.GetTransform().Translate(WORLD_FORWARD * -5.f);
	}

	void Sandbox::Load()
	{
		testMaterial = Material(Shader::Create("Assets/Shaders/Test.glsl"), 
			Texture::Create("Assets/Textures/Debug_White.png"));
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
		camera.GetTransform().SetRotation(glm::angleAxis(glm::radians(look.y), WORLD_RIGHT) * 
			camera.GetTransform().GetRotation() * 
			glm::angleAxis(glm::radians(look.x), WORLD_UP));
	}

	void Sandbox::Render()
	{
		m_Context->Clear(ClearFlags::Color | ClearFlags::Depth);

		testMaterial.GetShader()->Set("u_Projection", camera.GetProjectionMatrix());
		testMaterial.GetShader()->Set("u_View", camera.GetViewMatrix());
		testMaterial.GetShader()->Set("u_Transform", meshTransform.GetMatrix());

		testMaterial.Bind();
		m_Context->Render(Primitives::GetCube()->GetVertexArray());
		testMaterial.Unbind();
	}
}