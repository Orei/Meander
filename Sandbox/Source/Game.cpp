#include "Game.h"
#include "Components/Rotate.h"
#include "Actors/MeshActor.h"
#include "EditorSink.h"
#include <Meander/Meander.h>
#include <Platform/OpenGL/GLTexture.h>
#include <imgui/imgui.h>

using namespace Meander;

namespace Sandbox
{
	std::shared_ptr<EditorSink> consoleSink;
    World* world;
    FrameBuffer* fbo;
    Shader* testShader;
    Shader* procShader;
    CubeMap* skybox;
    Material* meshMaterial;
    Material* skyboxMaterial;
    Material* groundMaterial;
	Texture* consoleIcons = nullptr;
    PerspectiveCamera* camera;
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
    	// Push back our editor sink, which will handle messages for our console window
    	Log::Get()->sinks().push_back(consoleSink = std::make_shared<EditorSink>(300));
    	consoleSink->set_pattern("[%H:%M:%S] %v");

    	MN_TRACE("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
    	MN_INFO("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
    	MN_WARN("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
    	MN_ERROR("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");

    	// Create frame buffer
    	fbo = FrameBuffer::Create(m_Window->GetWidth(), m_Window->GetHeight());

        m_Window->SetVerticalSync(true);

    	// m_Window->SetOnResizeCallback([](unsigned int width, unsigned int height)
    	// {
    	// 	fbo->Resize(width, height);
    	// 	camera->SetAspectRatio(width / static_cast<float>(height));
    	// });

        m_RenderContext->SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
        m_RenderContext->SetDepthTest(true);
        m_RenderContext->SetBlend(true);
        m_RenderContext->SetCullFace(true);
        m_RenderContext->SetWindingOrder(WindingOrder::CounterClockwise);
        m_RenderContext->SetCullDirection(CullDirection::Back);

    	ImGuiIO io = ImGui::GetIO();
    	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    	ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = { 4.f, 4.f };
		style.FramePadding = { 6.f, 6.f };
    	style.WindowRounding = style.TabRounding = style.ChildRounding = 0.f;
    	style.WindowBorderSize = style.ChildBorderSize = style.PopupBorderSize = 1.f;
    	style.FrameBorderSize = 0.f;

    	ImVec4* colors = style.Colors;
		colors[ImGuiCol_Text]                   = { 1.f, 	1.f, 	1.f, 	1.f 	};
		colors[ImGuiCol_TextDisabled]           = { 0.f, 	0.f, 	0.f, 	1.f 	};
		colors[ImGuiCol_WindowBg]               = { 0.18f, 	0.18f, 	0.18f, 	1.f 	};
		colors[ImGuiCol_ChildBg]                = { 0.28f, 	0.28f, 	0.28f, 	0.f 	};
		colors[ImGuiCol_PopupBg]                = { 0.313f, 0.313f, 0.313f, 1.f 	};
		colors[ImGuiCol_Border]                 = { 0.266f, 0.266f, 0.266f, 1.f 	};
		colors[ImGuiCol_BorderShadow]           = { 0.f, 	0.f, 	0.f, 	0.f 	};
		colors[ImGuiCol_FrameBg]                = { 0.16f, 	0.16f, 	0.16f, 	1.f 	};
		colors[ImGuiCol_FrameBgHovered]         = { 0.f, 	0.f, 	0.f, 	1.f 	};
		colors[ImGuiCol_FrameBgActive]          = { 0.28f, 	0.28f, 	0.28f, 	1.f 	};
		colors[ImGuiCol_TitleBg]                = { 0.148f, 0.148f, 0.148f, 1.f 	};
		colors[ImGuiCol_TitleBgActive]          = { 0.148f, 0.148f, 0.148f, 1.f 	};
		colors[ImGuiCol_TitleBgCollapsed]       = { 0.148f, 0.148f, 0.148f, 1.f 	};
		colors[ImGuiCol_MenuBarBg]              = { 0.195f, 0.195f, 0.195f, 1.f 	};
		colors[ImGuiCol_ScrollbarBg]            = { 0.16f, 	0.16f, 	0.16f, 	1.f 	};
		colors[ImGuiCol_ScrollbarGrab]          = { 0.277f, 0.277f, 0.277f, 1.f 	};
		colors[ImGuiCol_ScrollbarGrabHovered]   = { 0.3f,	0.3f, 	0.3f, 	1.f 	};
		colors[ImGuiCol_ScrollbarGrabActive]    = { 1.f, 	0.391f, 0.f, 	1.f 	};
		colors[ImGuiCol_CheckMark]              = { 1.f, 	1.f, 	1.f, 	1.f 	};
		colors[ImGuiCol_SliderGrab]             = { 0.391f, 0.391f, 0.391f, 1.f 	};
		colors[ImGuiCol_SliderGrabActive]       = { 1.f, 	0.391f, 0.f, 	1.f 	};
		colors[ImGuiCol_Button]                 = { 1.f, 	1.f, 	1.f, 	0.f 	};
		colors[ImGuiCol_ButtonHovered]          = { 1.f, 	1.f, 	1.f, 	0.156f 	};
		colors[ImGuiCol_ButtonActive]           = { 1.f, 	1.f, 	1.f, 	0.391f 	};
		colors[ImGuiCol_Header]                 = { 0.313f, 0.313f, 0.313f, 1.f 	};
		colors[ImGuiCol_HeaderHovered]          = { 0.469f, 0.469f, 0.469f, 1.f 	};
		colors[ImGuiCol_HeaderActive]           = { 0.469f, 0.469f, 0.469f, 1.f 	};
		colors[ImGuiCol_Separator]              = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered]       = { 0.391f, 0.391f, 0.391f, 1.f 	};
		colors[ImGuiCol_SeparatorActive]        = { 1.f, 	0.391f, 0.f, 	1.f 	};
		colors[ImGuiCol_ResizeGrip]             = { 1.f, 	1.f, 	1.f, 	0.25f 	};
		colors[ImGuiCol_ResizeGripHovered]      = { 1.f, 	1.f, 	1.f, 	0.67f 	};
		colors[ImGuiCol_ResizeGripActive]       = { 1.f, 	0.391f, 0.f, 	1.f 	};
		colors[ImGuiCol_Tab]                    = { 0.098f, 0.098f, 0.098f, 1.f 	};
		colors[ImGuiCol_TabHovered]             = { 0.352f, 0.352f, 0.352f, 1.f 	};
		colors[ImGuiCol_TabActive]              = { 0.195f, 0.195f, 0.195f, 1.f 	};
		colors[ImGuiCol_TabUnfocused]           = { 0.098f, 0.098f, 0.098f, 1.f 	};
		colors[ImGuiCol_TabUnfocusedActive]     = { 0.195f, 0.195f, 0.195f, 1.f 	};
		colors[ImGuiCol_DockingPreview]         = { 1.f, 	0.391f, 0.f, 	0.781f	};
		colors[ImGuiCol_DockingEmptyBg]         = { 0.180f, 0.180f, 0.180f, 1.f 	};
		colors[ImGuiCol_PlotLines]              = { 0.469f, 0.469f, 0.469f, 1.f 	};
		colors[ImGuiCol_PlotLinesHovered]       = { 1.f, 	0.391f, 0.f, 	1.f 	};
		colors[ImGuiCol_PlotHistogram]          = { 0.586f, 0.586f, 0.586f, 1.f 	};
		colors[ImGuiCol_PlotHistogramHovered]   = { 1.f, 	0.391f, 0.f, 	1.f 	};
		colors[ImGuiCol_TextSelectedBg]         = { 1.f, 	1.f, 	1.f, 	0.156f	};
		colors[ImGuiCol_DragDropTarget]         = { 1.f, 	0.391f, 0.f, 	1.f 	};
		colors[ImGuiCol_NavHighlight]           = { 1.f, 	0.391f, 0.f, 	1.f 	};
		colors[ImGuiCol_NavWindowingHighlight]  = { 1.f, 	0.391f, 0.f, 	1.f 	};
		colors[ImGuiCol_NavWindowingDimBg]      = { 0.f, 	0.f, 	0.f, 	0.586f 	};
		colors[ImGuiCol_ModalWindowDimBg]       = { 0.f, 	0.f, 	0.f, 	0.586f 	};

    	io.Fonts->AddFontFromFileTTF("Assets/Fonts/Oxygen/Oxygen-Regular.ttf", 15.f);
    	
	    camera = new PerspectiveCamera(70.f, m_Window->GetAspectRatio());
	    camera->GetTransform().Translate(WORLD_FORWARD * -5.f);

	    world = new World();
    }

    void Game::Load()
    {
    	// Load UI stuff
    	consoleIcons = Resources::Load<Texture>("Assets/UI/Console_Icons.png");
    	
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
	 
		// Spawn actors
		auto ground = world->Spawn<MeshActor>("Ground", groundTransform);
		ground->GetStaticMesh()->SetMesh(Primitives::GetPlane());
		ground->GetStaticMesh()->SetMaterial(groundMaterial);
	 
		auto cube = world->Spawn<MeshActor>("Cube");
		cube->GetStaticMesh()->SetMesh(Primitives::GetCube());
		cube->GetStaticMesh()->SetMaterial(meshMaterial);
	 
		auto skybox = world->Spawn<MeshActor>("Skybox");
		skybox->GetStaticMesh()->SetMesh(Primitives::GetCube());
		skybox->GetStaticMesh()->SetMaterial(skyboxMaterial);
	 
		// Spawn some random cubes in the air
		for (int i = 0; i < 6; ++i)
		{
			glm::vec3 position = Random::Axis() * 5.f + WORLD_UP * 15.f;
			glm::vec3 rotation = Random::Axis();
		
			char name[ENTITY_NAME_LENGTH];
			sprintf_s(name, ENTITY_NAME_LENGTH, "Cube %i", i + 1);
	 
			auto rotatingCube = world->Spawn<MeshActor>(name, { position, rotation });
			rotatingCube->Create<CRotate>();
			rotatingCube->GetStaticMesh()->SetMesh(Primitives::GetCube());
			rotatingCube->GetStaticMesh()->SetMaterial(meshMaterial);
		}
    }

    void Game::Update(Meander::GameTime& gameTime)
    {
    	// TODO: Tick the world when "playing in editor"
    	// world->Tick(gameTime.GetDeltaSeconds());

    	const glm::vec3 movement = Input::GetKeysAxis(Key::A, Key::D) * camera->GetTransform().GetRight() +
    		Input::GetKeysAxis(Key::LeftControl, Key::Space) * WORLD_UP +
    		Input::GetKeysAxis(Key::S, Key::W) * camera->GetTransform().GetForward();
    	
    	camera->GetTransform().Translate(movement * gameTime.GetDeltaSeconds() * 4.f);
    	
    	if (!cursorDisabled)
    	{
    		const glm::vec2 look = Input::GetMouseDelta() * 0.05f;
    		camera->GetTransform().SetRotation(glm::angleAxis(glm::radians(look.y), WORLD_RIGHT) *
    			camera->GetTransform().GetRotation() *
    			glm::angleAxis(glm::radians(look.x), WORLD_UP));
    	}

    	// TODO: Needs to be called last, otherwise the camera will do some funky rotational stuff
    	if (Input::IsMousePressed(MouseButton::Right))
    	{
    		m_Window->SetCursorState(cursorDisabled = false);
    	}
    	else if (Input::IsMouseReleased(MouseButton::Right))
    	{
    		m_Window->SetCursorState(cursorDisabled = true);
    	}
    }

    void Game::Render(Meander::GameTime& gameTime)
    {
    	// Render scene to framebuffer
    	renderer.SetRenderTarget(fbo);

    	renderer.Begin(camera->GetViewMatrix(), camera->GetProjectionMatrix());
    	renderer.Clear(ClearFlags::Color | ClearFlags::Depth);
    	for (const auto& actor : world->GetActors())
    	{
    		if (!actor->IsEnabled())
    			continue;
    		
    		const auto& mesh = actor->Get<CStaticMesh>();
    		
    		// We can't render if it has no material or mesh, all entities have a transform
    		if (!mesh->GetMesh() || !mesh->GetMaterial())
    			continue;

    		renderer.Submit(actor->GetTransform(), mesh->GetMesh(), mesh->GetMaterial());
    	}
    	renderer.End();

    	// We're just clearing the screen, framebuffer will be rendered into a window
    	renderer.SetRenderTarget(nullptr);

    	renderer.Begin();
    	renderer.Clear(ClearFlags::Color | ClearFlags::Depth);
    	renderer.End();
    }

	static Actor* selectedActor = nullptr;
	static bool showGameWindow = true;
	static bool showHierarchyWindow = true;
	static bool showDetailsWindow = true;
	static bool showResourcesWindow = true;
	static bool showConsoleWindow = true;
	void ShowDockspace()
	{
	    static bool opt_fullscreen_persistant = true;
	    bool opt_fullscreen = opt_fullscreen_persistant;
	    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

	    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	    if (opt_fullscreen)
	    {
	        ImGuiViewport* viewport = ImGui::GetMainViewport();
	        ImGui::SetNextWindowPos(viewport->GetWorkPos());
	        ImGui::SetNextWindowSize(viewport->GetWorkSize());
	        ImGui::SetNextWindowViewport(viewport->ID);
	        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	    }

	    if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
	        windowFlags |= ImGuiWindowFlags_NoBackground;

	    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.f, 0.f });
	    ImGui::Begin("Viewport", (bool*)true, windowFlags);
	    ImGui::PopStyleVar();

	    if (opt_fullscreen)
	        ImGui::PopStyleVar(2);

	    ImGuiIO& io = ImGui::GetIO();
	    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	    {
	        ImGuiID dockspaceId = ImGui::GetID("Dockspace");
	        ImGui::DockSpace(dockspaceId, { 0.f, 0.f }, dockspaceFlags);
	    }

	    if (ImGui::BeginMenuBar())
	    {
	    	if (ImGui::BeginMenu("File"))
	    	{
	    		if (ImGui::MenuItem("Exit"))
	    			Application::Get()->Exit();

	    		ImGui::EndMenu();
	    	}
	    	
	        if (ImGui::BeginMenu("Views"))
	        {
				ImGui::MenuItem("Game", 0, &showGameWindow);
	        	ImGui::MenuItem("Hierarchy", 0, &showHierarchyWindow);
	        	ImGui::MenuItem("Details", 0, &showDetailsWindow);
	        	ImGui::MenuItem("Resources", 0, &showResourcesWindow);
	        	ImGui::MenuItem("Console", 0, &showConsoleWindow);

	            ImGui::EndMenu();
	        }

	        ImGui::EndMenuBar();
	    }

	    ImGui::End();
	}

	void ShowGameWindow()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.f, 0.f });
		if (ImGui::Begin("Game"))
		{
			GLTexture* texture = static_cast<GLTexture*>(fbo->GetColor());
			unsigned int handle = texture->GetHandle();

			const ImVec2& size = ImGui::GetContentRegionAvail();
			if (texture->GetWidth() != size.x || texture->GetHeight() != size.y)
			{
				fbo->Resize(size.x, size.y);
				camera->SetAspectRatio(size.x / size.y);
			}

			ImGui::Image((void*)handle, size, { 0.f, 1.f }, { 1.f, 0.f });
			ImGui::End();
		}
		ImGui::PopStyleVar();
	}

	void ShowTransformModule(Transform& transform)
	{
		if (ImGui::CollapsingHeader("Transform"))
		{
			const float itemHeight = ImGui::CalcTextSize("A", NULL, true).y + ImGui::GetStyle().FramePadding.y * 2.0f;

			const glm::vec3 position = transform.GetPosition();
			const glm::vec3 euler = transform.GetEuler();
			const glm::vec3 scale = transform.GetScale();
			float p[3] = { position.x, position.y, position.z };
			float r[3] = { glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z) };
			float s[3] = { scale.x, scale.y, scale.z };
				
			float x = Math::Max(ImGui::GetWindowSize().x, 300.f);
			float y = Math::Max(ImGui::GetWindowSize().y, itemHeight * 5.2f);
			ImGui::DragFloat3("Position", p, 0.1f);
			ImGui::DragFloat3("Rotation", r, 0.1f);
			ImGui::DragFloat3("Scale", s, 0.1f);
			
			transform.SetPosition({ p[0], p[1], p[2] });
			transform.SetEuler({ glm::radians(r[0]), glm::radians(r[1]), glm::radians(r[2]) });
			transform.SetScale({ s[0], s[1], s[2] });
		}
	}

	void ShowComponentModule(Component* component)
	{
		if (ImGui::CollapsingHeader(component->GetType().Name))
		{
		}
	}
	
	void ShowDetailsWindow()
	{
		if (ImGui::Begin("Details"))
		{
			if (selectedActor != nullptr)
			{
				ShowTransformModule(selectedActor->GetTransform());

				for (const auto& pair : selectedActor->GetComponents())
					ShowComponentModule(pair.second);
			}
			ImGui::End();
		}
	}
	
	void ShowHierarchyWindow()
	{
		if (ImGui::Begin("Hierarchy"))
		{
			const ImVec2& size = ImGui::GetContentRegionAvail();
			ImGui::ListBoxHeader("", size);
			
			static int selectedIndex = 0;
			const std::vector<Actor*>& actors = world->GetActors();
			for (int i = 0; i < actors.size(); ++i)
				if (ImGui::Selectable(actors[i]->GetName(), i == selectedIndex))
					selectedIndex = i;

			if (selectedIndex >= 0 && selectedIndex < actors.size())
				selectedActor = actors[selectedIndex];

			ImGui::ListBoxFooter();
			ImGui::End();
		}
	}

	void ShowResourcesWindow()
	{
		if (ImGui::Begin("Resources"))
		{
			ImGui::ListBoxHeader("", { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y });

			auto res = Resources::GetResources();
			for (auto it = res.begin(); it != res.end(); ++it)
				ImGui::TextUnformatted(Path::GetFileName(it->first).c_str());

			ImGui::ListBoxFooter();
			ImGui::End();
		}
	}

	void ShowConsoleWindow()
	{
		if (ImGui::Begin("Console"))
		{
			ImGui::ListBoxHeader("", { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y });
			
			float height = ImGui::GetTextLineHeightWithSpacing();
			static unsigned int handle = static_cast<GLTexture*>(consoleIcons)->GetHandle();
			static size_t numMessages = 0;

			for (auto& msg : consoleSink->GetFormatted())
			{
				int iconId = -1;
				switch (msg.Level)
				{
				default: break;
				case spdlog::level::trace: iconId = 0; break;
				case spdlog::level::info: iconId = 1; break;
				case spdlog::level::warn: iconId = 2; break;
				case spdlog::level::err: iconId = 3; break;
				}
				
				float x0 = (iconId * 48.f) / consoleIcons->GetWidth();
				float x1 = ((iconId + 1) * 48.f) / consoleIcons->GetWidth();

				ImVec4 color = consoleSink->GetLevelColor(msg.Level);
				ImGui::PushStyleColor(ImGuiCol_Text, color);
				ImGui::Image((void*)handle, { height, height }, { x0, 1.f }, { x1, 0.f }, color);
				ImGui::SameLine(0.f, 0.f);
				ImGui::TextWrapped(msg.Text.c_str());
				ImGui::PopStyleColor();
			}
			
			if (numMessages != consoleSink->NumMessages() && ImGui::GetScrollY() == ImGui::GetScrollMaxY())
			{
				numMessages = consoleSink->NumMessages();
				ImGui::SetScrollHereY(1.f);
			}
			
			ImGui::ListBoxFooter();
			ImGui::End();
		}
	}
	
	void Game::RenderUI(GameTime& gameTime)
	{
		ShowDockspace();
		if (showGameWindow) ShowGameWindow();
		if (showHierarchyWindow) ShowHierarchyWindow();
		if (showDetailsWindow) ShowDetailsWindow();
		if (showResourcesWindow) ShowResourcesWindow();
		if (showConsoleWindow) ShowConsoleWindow();
	}
}