#include "Game.h"
#include <Meander/Meander.h>
#include <Platform/OpenGL/GLTexture.h>
#include <imgui/imgui.h>

using namespace Meander;

namespace Sandbox
{
	Shared<FrameBuffer> fbo;
	Shared<Shader> procShader;
	Shared<CubeMap> skybox;
	Shared<Material> meshMaterial, skyboxMaterial, groundMaterial;
	Transform meshTransform, groundTransform;
	PerspectiveCamera camera(70.f, (float)1280 / 720);
	bool cursorDisabled = true;

	const char* sixFaces[] =
	{
		"Assets/Textures/SkyNight/X+.png", // X+ (Right)
		"Assets/Textures/SkyNight/X-.png", // X- (Left)
		"Assets/Textures/SkyNight/Y+.png", // Y+ (Top)
		"Assets/Textures/SkyNight/Y-.png", // Y- (Bottom)
		"Assets/Textures/SkyNight/Z+.png", // Z+ (Front)
		"Assets/Textures/SkyNight/Z-.png", // Z- (Back)
	};

	void Game::Initialize()
	{
		m_Window->SetVerticalSync(true);

		m_Context->SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
		m_Context->SetDepthTest(true);
		m_Context->SetBlend(true);
		m_Context->SetCullFace(true);
		m_Context->SetWindingOrder(WindingOrder::CounterClockwise);
		m_Context->SetCullDirection(CullDirection::Back);

		fbo = FrameBuffer::Create(1280, 720);

		// Move the camera back, so we can see the center
		camera.GetTransform().Translate(WORLD_FORWARD * -5.f);
	}

	void Game::Load()
	{
		meshMaterial.reset(new Material(Shader::Create("Assets/Shaders/Test.glsl"),
			Texture::Create("Assets/Textures/Debug_White.png")));

		procShader = Shader::Create("Assets/Shaders/PostEffect.glsl");

		skybox = CubeMap::Create(sixFaces);
		skyboxMaterial.reset(new Material(Shader::Create("Assets/Shaders/Skybox.glsl")));

		groundMaterial.reset(new Material(Shader::Create("Assets/Shaders/Test.glsl"),
			Texture::Create("Assets/Textures/Debug_Black.png")));

		groundTransform.Translate(-WORLD_UP / 2.f);
		groundTransform.Rotate(glm::radians(-90.f), WORLD_RIGHT);
	}

	void Game::Update(GameTime& gameTime)
	{
		if (Input::IsKeyPressed(Key::Escape))
			Exit();

		if (Input::IsMousePressed(MouseButton::Right))
			m_Window->SetCursorState(cursorDisabled = false);
		else if (Input::IsMouseReleased(MouseButton::Right))
			m_Window->SetCursorState(cursorDisabled = true);

		glm::vec3 movement = Input::GetKeysAxis(Key::A, Key::D) * camera.GetTransform().GetRight() +
			Input::GetKeysAxis(Key::LeftControl, Key::Space) * WORLD_UP +
			Input::GetKeysAxis(Key::S, Key::W) * camera.GetTransform().GetForward();

		camera.GetTransform().Translate(movement * gameTime.GetDeltaSeconds() * 4.f);

		if (cursorDisabled)
			return;

		glm::vec2 look = Input::GetMouseDelta() * 0.05f;
		camera.GetTransform().SetRotation(glm::angleAxis(glm::radians(look.y), WORLD_RIGHT) *
			camera.GetTransform().GetRotation() *
			glm::angleAxis(glm::radians(look.x), WORLD_UP));
	}

	void Game::Render(GameTime& gameTime)
	{
		// Render the scene to the frame buffer
		Renderer::SetRenderTarget(fbo);

		Renderer::Begin(camera.GetViewMatrix(), camera.GetProjectionMatrix());
		Renderer::Clear(ClearFlags::Color | ClearFlags::Depth);
		Renderer::Render(meshTransform, Primitives::GetCube(), meshMaterial);
		Renderer::Render(groundTransform, Primitives::GetPlane(), groundMaterial);
		Renderer::Render({}, Primitives::GetCube(), skyboxMaterial);
		Renderer::End();

		// Render the frame buffer to the screen
		Renderer::SetRenderTarget(nullptr);

		Renderer::Begin();
		Renderer::Clear(ClearFlags::Color | ClearFlags::Depth);
		Renderer::Render(fbo, procShader);
		Renderer::End();
	}
	
	unsigned int fboDepthHandle = 0; 
	void Game::OnGui(GameTime& gameTime)
	{
		float deltaMs = gameTime.GetDeltaSeconds() * 1000.f;
		int fps = (int)round(1.f / gameTime.GetDeltaSeconds());

		ImGui::Begin("Statistics", (bool*)0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::SetWindowPos({ 8.f, 8.f });
		ImGui::Text("%f ms (%i FPS)\nElapsed Time: %f", deltaMs, fps, gameTime.GetTimeElapsed());
		ImGui::End();

		glm::vec3 position = camera.GetTransform().GetPosition();
		glm::vec3 euler = camera.GetTransform().GetEuler();
		glm::vec3 scale = camera.GetTransform().GetScale();
		float p[3] = { position.x, position.y, position.z };
		float r[3] = { glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z) };
		float s[3] = { scale.x, scale.y, scale.z };

		ImGui::Begin("Transform");
		ImGui::SetWindowSize({ 300.f, ImGui::GetWindowHeight() });
		ImGui::DragFloat3("Position", p);
		ImGui::DragFloat3("Rotation", r);
		ImGui::DragFloat3("Scale", s);
		ImGui::End();

		camera.GetTransform().SetPosition({ p[0], p[1], p[2] });
		camera.GetTransform().SetEuler({ glm::radians(r[0]), glm::radians(r[1]), glm::radians(r[2]) });
		camera.GetTransform().SetScale({ s[0], s[1], s[2] });

		if (fboDepthHandle == 0 && fbo != nullptr && fbo->GetDepth() != nullptr)
		{
			auto texture = fbo->GetDepth();
			auto glTex = std::dynamic_pointer_cast<GLTexture>(texture);
			fboDepthHandle = glTex->GetHandle();
		}

		ImGui::Begin("Depth Buffer");
		ImGui::Image((void*)fboDepthHandle, { 320, 180 }, { 0.f, 1.f }, { 1.f, 0.f });
		ImGui::End();
	}
}