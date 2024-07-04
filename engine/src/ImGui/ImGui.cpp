#include "ImGui.h"
#include "Theme.h"

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>

namespace Engine {
    ImGui::ImGui(GLFWwindow* window, Theme* theme) {
        const char* glsl_version = "#version 330";
        ::IMGUI_CHECKVERSION();
        ::ImGui::CreateContext();
        ImGuiIO& io = ::ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        if(theme)
            theme->SetTheme();
        else    
            ::ImGui::StyleColorsDark();
        
        ::ImGui_ImplGlfw_InitForOpenGL(window, true);
        ::ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void ImGui::OnImGuiRender(Function function) {
        function();
    }

    void ImGui::SetImGuiContext(::ImGuiContext* ctx) {
        ::ImGui::SetCurrentContext(ctx);
    }

    ::ImGuiContext* ImGui::GetImGuiContext() {
        return ::ImGui::GetCurrentContext();
    }
}