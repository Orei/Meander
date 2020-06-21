#include "Game.h"
#include "Components/CRotate.h"
#include "Entities/BasicEntity.h"
#include <Meander/Meander.h>
#include <Platform/OpenGL/GLTexture.h>
#include <imgui/imgui.h>

using namespace Meander;

namespace Sandbox
{
    World* world;
    FrameBuffer* fbo;
    Shader* testShader;
    Shader* procShader;
    CubeMap* skybox;
    Material* meshMaterial;
    Material* skyboxMaterial;
    Material* groundMaterial;
    PerspectiveCamera* camera;
    ForwardRenderer renderer;
    Random random;
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
    	fbo = FrameBuffer::Create(m_Window->GetWidth(), m_Window->GetHeight());

        m_Window->SetVerticalSync(true);
    	m_Window->SetOnResizeCallback([](unsigned int width, unsigned int height)
    	{
    		fbo->Resize(width, height);
    		camera->SetAspectRatio(width / static_cast<float>(height));
    	});

        m_RenderContext->SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
        m_RenderContext->SetDepthTest(true);
        m_RenderContext->SetBlend(true);
        m_RenderContext->SetCullFace(true);
        m_RenderContext->SetWindingOrder(WindingOrder::CounterClockwise);
        m_RenderContext->SetCullDirection(CullDirection::Back);

	    camera = new PerspectiveCamera(70.f, m_Window->GetAspectRatio());
	    camera->GetTransform().Translate(WORLD_FORWARD * -5.f);

	    world = new World();
    }

    void Game::Load()
    {
    	// TODO: Skybox cubemap is bound forever, but we might want to bind other cubemaps at some point
		// Renderer should be able to handle rendering skyboxes properly
		skyboxMaterial = new Material(Resources::Load<Shader>("Assets/Shaders/Skybox.glsl"));
		skybox = CubeMap::Create(sixFaces);
		skybox->Bind();

		// Load shaders and create materials
		testShader = Resources::Load<Shader>("Assets/Shaders/Test.glsl");
		procShader = Resources::Load<Shader>("Assets/Shaders/PostEffect.glsl");
		meshMaterial = new Material(testShader, Resources::Load<Texture>("Assets/Textures/Debug_White.png"));
		groundMaterial = new Material(testShader, Resources::Load<Texture>("Assets/Textures/Debug_Black.png"));
	 
		// Move down half a unit and rotate plane so it faces upwards
		Transform groundTransform(-WORLD_UP / 2.f, 
			glm::angleAxis(glm::radians(-90.f), WORLD_RIGHT));
	 
		// Create entities
		auto ground = world->Spawn<BasicEntity>("Ground", groundTransform);
		ground->GetMesh()->SetMesh(Primitives::GetPlane());
		ground->GetMesh()->SetMaterial(groundMaterial);
	 
		auto cube = world->Spawn<BasicEntity>("Cube");
		cube->GetMesh()->SetMesh(Primitives::GetCube());
		cube->GetMesh()->SetMaterial(meshMaterial);
	 
		auto skybox = world->Spawn<BasicEntity>("Skybox");
		skybox->GetMesh()->SetMesh(Primitives::GetCube());
		skybox->GetMesh()->SetMaterial(skyboxMaterial);
	 
		// Spawn some random cubes in the air
		for (int i = 0; i < 6; ++i)
		{
			glm::vec3 position = random.Axis() * 5.f + WORLD_UP * 15.f;
			glm::vec3 rotation = random.Axis();
		
			char name[ENTITY_NAME_LENGTH];
			sprintf_s(name, ENTITY_NAME_LENGTH, "Cube %i", i + 1);
	 
			auto rotatingCube = world->Spawn<BasicEntity>(name, { position, rotation });
			rotatingCube->Create<CRotate>();
			rotatingCube->GetMesh()->SetMesh(Primitives::GetCube());
			rotatingCube->GetMesh()->SetMaterial(meshMaterial);
		}
    }

    void Game::Update(Meander::GameTime& gameTime)
    {
    	if (Input::IsKeyPressed(Key::Escape))
    	{
    		m_Application->Exit();
    		return;
    	}

    	world->Tick(gameTime.GetDeltaSeconds());
    	
    	if (Input::IsMousePressed(MouseButton::Right))
    	{
    		// Camera does some funky rotation stuff if we don't return here
    		m_Window->SetCursorState(cursorDisabled = false);
    		return;
    	}
    	else if (Input::IsMouseReleased(MouseButton::Right))
    	{
    		m_Window->SetCursorState(cursorDisabled = true);
    		return;
    	}
    	
    	const glm::vec3 movement = Input::GetKeysAxis(Key::A, Key::D) * camera->GetTransform().GetRight() +
    		Input::GetKeysAxis(Key::LeftControl, Key::Space) * WORLD_UP +
    		Input::GetKeysAxis(Key::S, Key::W) * camera->GetTransform().GetForward();
    	
    	camera->GetTransform().Translate(movement * gameTime.GetDeltaSeconds() * 4.f);
    	
    	if (cursorDisabled)
    		return;
    	
    	const glm::vec2 look = Input::GetMouseDelta() * 0.05f;
    	camera->GetTransform().SetRotation(glm::angleAxis(glm::radians(look.y), WORLD_RIGHT) *
    		camera->GetTransform().GetRotation() *
    		glm::angleAxis(glm::radians(look.x), WORLD_UP));
    }

    void Game::Render(Meander::GameTime& gameTime)
    {
    	// Render scene to framebuffer
    	renderer.SetRenderTarget(fbo);

    	renderer.Begin(camera->GetViewMatrix(), camera->GetProjectionMatrix());
    	renderer.Clear(ClearFlags::Color | ClearFlags::Depth);
    	for (const auto& entity : world->GetEntities())
    	{
    		if (!entity->IsEnabled())
    			continue;
    		
    		const auto& mesh = entity->Get<CStaticMesh>();
    		
    		// We can't render if it has no material or mesh, entities always have a transform
    		if (!mesh->GetMesh() || !mesh->GetMaterial())
    			continue;

    		renderer.Submit(entity->GetTransform(), mesh->GetMesh(), mesh->GetMaterial());
    	}
    	renderer.End();

    	// Render framebuffer to screen
    	renderer.SetRenderTarget(nullptr);

    	renderer.Begin();
    	renderer.Clear(ClearFlags::Color | ClearFlags::Depth);
    	renderer.Render(fbo, procShader);
    	renderer.End();
    }

	static int selectedIndex = 0;
	static Entity* selectedEntity = nullptr;	
	void TransformWindow()
	{
		if (selectedEntity != nullptr)
		{
			const float itemHeight = ImGui::CalcTextSize("A", NULL, true).y + ImGui::GetStyle().FramePadding.y * 2.0f;

			const glm::vec3 position = selectedEntity->GetTransform().GetPosition();
			const glm::vec3 euler = selectedEntity->GetTransform().GetEuler();
			const glm::vec3 scale = selectedEntity->GetTransform().GetScale();
			float p[3] = { position.x, position.y, position.z };
			float r[3] = { glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z) };
			float s[3] = { scale.x, scale.y, scale.z };

			ImGui::Begin("Transform");
			float x = Math::Max(ImGui::GetWindowSize().x, 300.f);
			float y = Math::Max(ImGui::GetWindowSize().y, itemHeight * 5.2f);
			ImGui::SetWindowSize({ x, y });
			ImGui::DragFloat3("Position", p, 0.1f);
			ImGui::DragFloat3("Rotation", r, 0.1f);
			ImGui::DragFloat3("Scale", s, 0.1f);
			ImGui::End();
		
			selectedEntity->GetTransform().SetPosition({ p[0], p[1], p[2] });
			selectedEntity->GetTransform().SetEuler({ glm::radians(r[0]), glm::radians(r[1]), glm::radians(r[2]) });
			selectedEntity->GetTransform().SetScale({ s[0], s[1], s[2] });
		}
	}

	void EntitiesWindow()
	{
		const float actionButtonHeight = ImGui::CalcTextSize("A", NULL, true).y + ImGui::GetStyle().FramePadding.y * 2.0f;
		
        std::vector<Entity*> entities = world->GetEntities();
        
        ImGui::Begin("Entities");
        ImGui::ListBoxHeader("", { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - actionButtonHeight * 1.2f });
        
        for (int i = 0; i < entities.size(); ++i)
        	if (ImGui::Selectable(entities[i]->GetName(), i == selectedIndex))
        		selectedIndex = i;

        ImGui::ListBoxFooter();

		const int numActions = 2;
		const float actionButtonWidth = ImGui::GetContentRegionAvail().x / numActions - ImGui::GetStyle().FramePadding.x;
        if (ImGui::Button("Spawn", { actionButtonWidth, actionButtonHeight }))
        {
        	static Material* spawnedMaterial = new Material(testShader, Texture::Create("Assets/Textures/Debug_Red.png"));
        	
        	if (!Input::IsKeyDown(Key::LeftShift))
        	{
        		const auto& spawned = world->Spawn<BasicEntity>("Entity");
        		spawned->GetMesh()->SetMesh(Primitives::GetCube());
        		spawned->GetMesh()->SetMaterial(spawnedMaterial);
        		spawned->Create<CRotate>();
        	}
        	else
        	{
        		for (int i = 0; i < 10; ++i)
        		{
        			const auto& spawned = world->Spawn<BasicEntity>("Entity");
        			spawned->GetMesh()->SetMesh(Primitives::GetCube());
        			spawned->GetMesh()->SetMaterial(spawnedMaterial);
        			spawned->Create<CRotate>();
        		}
        	}
        }

        selectedEntity = nullptr;
        if (selectedIndex >= 0 && selectedIndex < entities.size())
        	selectedEntity = entities[selectedIndex];
        
        if (selectedEntity != nullptr)
        {
        	ImGui::SameLine();
        	if (ImGui::Button("Destroy", { actionButtonWidth, actionButtonHeight }))
        		selectedEntity->Destroy();
        }
        
        ImGui::End();
	}
	
	void ResourcesWindow()
	{
		ImGui::Begin("Resources");
		ImGui::ListBoxHeader("", { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y });

		auto res = Resources::GetResources();
		for (auto it = res.begin(); it != res.end(); ++it)
			ImGui::Text("%s", Path::GetFileName(it->first).c_str());

		ImGui::ListBoxFooter();
		ImGui::End();
	}

	void StatisticsWindow(GameTime& gameTime)
	{
		const float deltaMs = gameTime.GetDeltaSeconds() * 1000.f;
		const int fps = (int)round(1.f / gameTime.GetDeltaSeconds());

		ImGui::Begin("Statistics", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::SetWindowPos({ 8.f, 24.f });
		ImGui::Text("%f ms (%i FPS)\nElapsed Time: %f\nEntities: %i\nSelected Index: %i",
            deltaMs, fps, gameTime.GetTimeElapsed(), world->NumEntities(), selectedIndex);
		ImGui::End();
	}

	void DepthBufferWindow()
	{
		static unsigned int fboDepthHandle = 0; 
		if (fboDepthHandle == 0 && fbo != nullptr && fbo->GetDepth() != nullptr)
		{
			const auto texture = fbo->GetDepth();

			if (texture != nullptr)
			{
				const auto glTex = static_cast<GLTexture*>(texture);
				fboDepthHandle = glTex->GetHandle();
			}
		}

		if (fboDepthHandle != 0)
		{
			ImGui::Begin("Depth Buffer");
			ImGui::Image((void*)fboDepthHandle, ImGui::GetContentRegionAvail(), { 0.f, 1.f }, { 1.f, 0.f });
			ImGui::End();
		}
	}

	void Game::RenderUI(GameTime& gameTime)
	{
		static bool showTrans = false;
		static bool showEnts = false;
		static bool showRes = false;
		static bool showStats = true;
		static bool showDepth = false;

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Views"))
			{
				ImGui::MenuItem("Transform", NULL, &showTrans);
				ImGui::MenuItem("Entities", NULL, &showEnts);
				ImGui::MenuItem("Resources", NULL, &showRes);
				ImGui::Separator();
				ImGui::MenuItem("Statistics", NULL, &showStats);
				ImGui::MenuItem("Depth Buffer", NULL, &showDepth);
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		if (showTrans) TransformWindow();
		if (showEnts) EntitiesWindow();
		if (showRes) ResourcesWindow();
		if (showStats) StatisticsWindow(gameTime);
		if (showDepth) DepthBufferWindow();
	}
}