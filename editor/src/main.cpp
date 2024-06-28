#include "ImGui/Theme.h"
#include "Menu/Menu.h"

#include <Assets/Asset.h>
#include <Assets/AssetDatabase.h>
#include <Core/Application.h>
#include <Debug/Logger.h>
#include <Renderer/RendererAPI.h>
#include <Scripting/Scripting.h>

#include <GLFW/glfw3.h>
#include <cstddef>
#include <filesystem>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string>
#include <vector>

#ifdef _WIN32
    #include <Windows.h>
    #include <winbase.h>
#endif

std::string convertToString(const std::shared_ptr<std::vector<std::byte>>& byteVectorPtr) {
    if (!byteVectorPtr) {
        throw std::invalid_argument("Null pointer passed to convertToString");
    }

    const auto& byteVector = *byteVectorPtr; // Dereference shared_ptr to get the vector
    std::string result;

    // Reserve space in the string to avoid multiple reallocations
    result.reserve(byteVector.size());

    // Convert each std::byte to char and append to the string
    for (std::byte b : byteVector) {
        result += static_cast<char>(b);
    }

    return result;
}

void testCallback() {
    std::cout << "Callback Called" << std::endl;
}

int main(int argc, char* argv[]) {
    #ifdef _WIN32
        SetDllDirectory(std::filesystem::current_path().string().c_str());
    #endif

    Theme* theme = new Theme("C:\\Users\\Pedro Bentes\\Desktop\\ParagonGameEngine\\editor\\themes\\steam.toml");
    
    if (argc <= 1 || !std::filesystem::is_regular_file(argv[1])) {
        Logger::GetInstance().Error("No path to the project provided. Aborting.");
        abort();
    }
    std::filesystem::current_path(std::filesystem::path(argv[1]).remove_filename().string());

    const int screenWidth = 800;
    const int screenHeight = 450;

    Application* app = new Application(screenWidth, screenHeight, (char*)"Paragon Game Engine");
    GLFWwindow* window = app->GetWindow();

    AssetDatabase* asset_db = new AssetDatabase((std::filesystem::current_path() / "assets").string());
    
    std::vector<size_t> scriptIDs = asset_db->SelectAssets("SELECT * FROM assets WHERE EXTENSION like '.wren'", 0);
    for(const size_t& id : scriptIDs) {
        std::shared_ptr<Asset> asset = asset_db->GetAssetByID(id);
        asset->LoadAsset();

        std::cout << asset->m_Path << std::endl;

        std::shared_ptr<std::vector<std::byte>> blob = asset->m_Blob;
        std::string source = convertToString(blob);
        asset->UnloadAsset();
        Scripting::GetInstance().Interpret("main", source);
    } 

    const char* glsl_version = "#version 330";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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

            Menu::GetInstance().AddMenuItem("File/Quit", "Ctrl+Q", [window]() {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            });

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