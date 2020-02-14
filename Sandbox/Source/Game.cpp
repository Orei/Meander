#include "Game.h"
#include <Meander/Meander.h>
#include <Platform/OpenGL/GLTexture.h>
#include <imgui/imgui.h>

using namespace Meander;

namespace Sandbox
{
	Scene scene;
	FrameBuffer* fbo;
	Shader* procShader;
	CubeMap* skybox;
	Material* meshMaterial;
	Material* skyboxMaterial;
	Material* groundMaterial;
	PerspectiveCamera camera(70.f, (float)1280 / 720);
	ForwardRenderer renderer;
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
		// TODO: Skybox cubemap is bound forever, but we might want to bind other cubemaps at some point
		// Renderer should be able to handle rendering skyboxes properly
		skyboxMaterial = new Material(Shader::Create("Assets/Shaders/Skybox.glsl"));
		skybox = CubeMap::Create(sixFaces);
		skybox->Bind();

		meshMaterial = new Material(Shader::Create("Assets/Shaders/Test.glsl"),
			Texture::Create("Assets/Textures/Debug_White.png"));

		groundMaterial = new Material(Shader::Create("Assets/Shaders/Test.glsl"),
			Texture::Create("Assets/Textures/Debug_Black.png"));

		procShader = Shader::Create("Assets/Shaders/PostEffect.glsl");

		// Move down half a unit and rotate plane so it faces upwards
		Transform groundTransform(-WORLD_UP / 2.f, 
			glm::angleAxis(glm::radians(-90.f), WORLD_RIGHT));

		// Create nodes for all objects
		scene.CreateNode(groundTransform, Primitives::GetPlane(), groundMaterial);
		scene.CreateNode({}, Primitives::GetCube(), meshMaterial);
		scene.CreateNode({}, Primitives::GetCube(), skyboxMaterial);
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
		// Render scene to framebuffer
		renderer.SetRenderTarget(fbo);

		renderer.Begin(camera.GetViewMatrix(), camera.GetProjectionMatrix());
		renderer.Clear(ClearFlags::Color | ClearFlags::Depth);
		for (const auto& node : scene.GetNodes())
		{
			// We can't render if it has no material or mesh, nodes always have a transform
			if (!node->GetMesh() || !node->GetMaterial())
				continue;

			renderer.Submit(node->GetTransform(), node->GetMesh(), node->GetMaterial());
		}
		renderer.End();

		// Render framebuffer to screen
		renderer.SetRenderTarget(nullptr);

		renderer.Begin();
		renderer.Clear(ClearFlags::Color | ClearFlags::Depth);
		renderer.Render(fbo, procShader);
		renderer.End();
	}
	
	unsigned int fboDepthHandle = 0; 
	void Game::OnGui(GameTime& gameTime)
	{
		/* Statistics */
		float deltaMs = gameTime.GetDeltaSeconds() * 1000.f;
		int fps = (int)round(1.f / gameTime.GetDeltaSeconds());

		ImGui::Begin("Statistics", (bool*)0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::SetWindowPos({ 8.f, 8.f });
		ImGui::Text("%f ms (%i FPS)\nElapsed Time: %f", deltaMs, fps, gameTime.GetTimeElapsed());
		ImGui::End();

		/* Depth Buffer */
		if (fboDepthHandle == 0 && fbo != nullptr && fbo->GetDepth() != nullptr)
		{
			auto texture = fbo->GetDepth();
			auto glTex = static_cast<GLTexture*>(texture);
			fboDepthHandle = glTex->GetHandle();
		}

		ImGui::Begin("Depth Buffer");
		ImGui::Image((void*)fboDepthHandle, { 320, 180 }, { 0.f, 1.f }, { 1.f, 0.f });
		ImGui::End();

		/* Nodes */
		static int selectedNode = 0;
		std::vector<SceneNode*> nodes = scene.GetNodes();
		int numNodes = (int)nodes.size();

		ImGui::Begin("Nodes");
		ImGui::ListBoxHeader("", numNodes);

		int i = 0;
		for (const auto& node : nodes)
		{
			if (ImGui::Selectable(node->GetName(), selectedNode == i))
				selectedNode = i;

			i++;
		}

		ImGui::ListBoxFooter();
		ImGui::End();

		/* Transform */
		SceneNode* activeNode = nullptr;

		if (selectedNode >= 0 && selectedNode < numNodes)
			activeNode = nodes[selectedNode];

		if (activeNode != nullptr)
		{
			glm::vec3 position = activeNode->GetTransform().GetPosition();
			glm::vec3 euler = activeNode->GetTransform().GetEuler();
			glm::vec3 scale = activeNode->GetTransform().GetScale();
			float p[3] = { position.x, position.y, position.z };
			float r[3] = { glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z) };
			float s[3] = { scale.x, scale.y, scale.z };

			ImGui::Begin("Transform");
			ImGui::SetWindowSize({ 300.f, ImGui::GetWindowHeight() });
			ImGui::DragFloat3("Position", p, 0.1f);
			ImGui::DragFloat3("Rotation", r, 0.1f);
			ImGui::DragFloat3("Scale", s, 0.1f);
			ImGui::End();

			activeNode->GetTransform().SetPosition({ p[0], p[1], p[2] });
			activeNode->GetTransform().SetEuler({ glm::radians(r[0]), glm::radians(r[1]), glm::radians(r[2]) });
			activeNode->GetTransform().SetScale({ s[0], s[1], s[2] });
		}
	}
}