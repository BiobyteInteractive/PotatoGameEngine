#include "ImGui/Theme.h"

#include <Assets/AssetDatabase.h>
#include <Core/Application.h>
#include <Debug/Logger.h>
#include <Renderer/RendererAPI.h>

#include <GLFW/glfw3.h>
#include <filesystem>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#ifdef _WIN32
    #include <Windows.h>
    #include <winbase.h>
#endif

int main() {
    Theme* theme = new Theme("C:\\Users\\Pedro Bentes\\Desktop\\ParagonGameEngine\\editor\\themes\\steam.toml");

    #ifdef _WIN32
        SetDllDirectory(std::filesystem::current_path().string().c_str());
        std::filesystem::current_path("C:\\Users\\Pedro Bentes\\Desktop\\GameEngineProject");
    #endif

    const int screenWidth = 800;
    const int screenHeight = 450;

    Application* app = new Application(screenWidth, screenHeight, (char*)"Paragon Game Engine");
    GLFWwindow* window = app->GetWindow();

    AssetDatabase* asset_db = new AssetDatabase((std::filesystem::current_path() / "assets").string());

    //InitAssetManager();

    const char* glsl_version = "#version 330";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // Todo: io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    
    theme->SetTheme();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    RendererAPI* renderer = app->m_Renderer;

    renderer->SetContext(app->m_Window);

    bool show_demo_window = true;
    while(!app->WindowShouldClose()) {


            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("Create")) { 
                    }
                    if (ImGui::MenuItem("Open", "Ctrl+O")) { 
                    }
                    if (ImGui::MenuItem("Save", "Ctrl+S")) {
                    }
                    if (ImGui::MenuItem("Save as..")) { 
                    }
                    if (ImGui::MenuItem("Quit", "Ctrl+Q")){ 
                        glfwSetWindowShouldClose(window, GLFW_TRUE);
                    }
                ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }

            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

            renderer->ClearBackground(255, 0, 255, 255);
            ImGui::ShowDemoWindow(&show_demo_window);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        renderer->EndDrawing();
    }

    delete asset_db;
    
    return 0;
}