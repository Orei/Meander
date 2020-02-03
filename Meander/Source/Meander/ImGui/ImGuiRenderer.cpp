#include "pch.h"
#include "ImGuiRenderer.h"
#include "Meander/Graphics/Context.h"
#include "Platform/GLFW/GLFWWindow.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <examples/imgui_impl_opengl3.cpp>
#include <examples/imgui_impl_glfw.cpp>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>

namespace Meander
{
	void ImGuiRenderer::Initialize()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		Window* window = Window::Get();
		Context* context = Context::Get();

		switch (context->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			ImGui_ImplOpenGL3_Init("#version 410");
			break;
		}

		switch (window->GetWindowAPI())
		{
		case WindowAPI::GLFW:
			GLFWWindow* glfwWindow = static_cast<GLFWWindow*>(window);
			ImGui_ImplGlfw_InitForOpenGL(glfwWindow->GetNativeWindow(), true);
			break;
		}
	}

	void ImGuiRenderer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiRenderer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}