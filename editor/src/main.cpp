#include <Engine.h>
#include <Assets/AssetDatabase.h>

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
    #ifdef _WIN32
        SetDllDirectory(std::filesystem::current_path().string().c_str());
        std::filesystem::current_path("C:\\Users\\Pedro Bentes\\Desktop\\GameEngineProject");
    #endif

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, (char*)"Potato Game Engine Editor");
    GLFWwindow* window = GetWindow();

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

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    while(!WindowShouldClose()) {
        BeginDrawing();
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

            ClearBackground(255, 0, 255, 255);
            ImGui::ShowDemoWindow(&show_demo_window);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        EndDrawing();
    }

    delete asset_db;
    
    return 0;
}