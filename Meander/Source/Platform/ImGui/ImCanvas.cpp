#include "pch.h"
#include "ImCanvas.h"

// TODO: Contains GLAD/GLFW specific stuff

#include "Meander/Graphics/RenderContext.h"
#include "Platform/GLFW/GLFWWindow.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui_impl_opengl3.cpp>
#include <imgui_impl_glfw.cpp>

namespace Meander
{
    void ImCanvas::Initialize(Window* window, RenderContext* renderer)
    {
        m_Window = window;
        m_Renderer = renderer;
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();

        switch (m_Renderer->GetContextAPI())
        {
        case RenderContextAPI::OpenGL:
            ImGui_ImplOpenGL3_Init("#version 410");
            break;
        }

        switch (m_Window->GetWindowAPI())
        {
        case WindowAPI::GLFW:
            GLFWWindow* glfwWindow = static_cast<GLFWWindow*>(m_Window);
            ImGui_ImplGlfw_InitForOpenGL(glfwWindow->GetNativeWindow(), true);
            break;
        }
    }

    void ImCanvas::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImCanvas::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
