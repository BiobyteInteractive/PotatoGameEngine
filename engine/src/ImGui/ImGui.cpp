#include "ImGui.h"

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_wgpu.h>
#include <imgui.h>

namespace Engine {
    ImGui::ImGui(GLFWwindow* window) {
        const char* glsl_version = "#version 330";
        ::IMGUI_CHECKVERSION();
        ::ImGui::CreateContext();
        ::ImGuiIO& io = ::ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        float xscale;
        glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &xscale, NULL);
        io.FontGlobalScale = xscale;

        ::ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplGlfw_InitForOther(window, true);

        ImGui_ImplWGPU_InitInfo init_info;
        init_info.Device = wgpu_device;
        init_info.NumFramesInFlight = 3;
        init_info.RenderTargetFormat = wgpu_preferred_fmt;
        init_info.DepthStencilFormat = WGPUTextureFormat_Undefined;
        ImGui_ImplWGPU_Init();
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

    void ImGui::StartFrame() {
        ImGui_ImplWGPU_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ::ImGui::NewFrame();
    }

    void ImGui::EndFrame() {
        ::ImGui::Render();
        ImGui_ImplWGPU_RenderDrawData(::ImGui::GetDrawData());

        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ::ImGui::UpdatePlatformWindows();
        ::ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}
