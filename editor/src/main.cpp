#include "Utils/FileUtils.h"

#include "ImGui/ImGui.h"
#include "Panels/ContentBrowserPanel.h"
#include "ImGui/Theme.h"
#include "ImGui/Menu.h"
#include "Renderer/OpenGL/OpenGL.h"

#include <Assets/Asset.h>
#include <Assets/AssetDatabase.h>
#include <Core/Application.h>
#include <Debug/Logger.h>
#include <Renderer/Color.h>
#include <Renderer/RendererAPI.h>
#include <Scripting/Scripting.h>

#include <GLFW/glfw3.h>
#include <cstddef>
#include <filesystem>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <memory>
#include <stdlib.h>
#include <string>
#include <vector>

#include <Windows.h>
#include <winbase.h>
#include <shobjidl.h> 

using namespace Engine;

std::string getExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

int main(int argc, char* argv[]) {
    #ifdef _WIN32
        SetDllDirectory(std::filesystem::current_path().string().c_str());
    #endif

    std::string projectPath;
    
    if (argc <= 1 || !std::filesystem::is_regular_file(argv[1])) {
        Logger::GetInstance().Info("No path to the project provided. Opening file prompt.");

        // Keep trying to open a file
        projectPath = OpenFileDialog();
        if(projectPath.empty() || !std::filesystem::path(projectPath).has_filename())
            return 0;
    } else {
        projectPath = std::string(argv[1]);
    }
    std::filesystem::current_path(std::filesystem::path(projectPath).remove_filename().string());

    const int screenWidth = 800;
    const int screenHeight = 450;

    Application app(screenWidth, screenHeight, (char*)"Paragon Game Engine");
    GLFWwindow* window = app.GetWindow();
    OpenGL* renderer = &app.m_Renderer;

    AssetDatabase asset_db((std::filesystem::current_path() / "assets").string());
    
    std::vector<size_t> scriptIDs = asset_db.SelectAssets("SELECT * FROM assets WHERE EXTENSION like '.wren' AND DIRECTORY like '%editor%'", 0);
    for(const size_t& id : scriptIDs) {
        std::shared_ptr<Asset> asset = asset_db.GetAssetByID(id);
        asset->LoadAssetSync();

        std::shared_ptr<std::vector<std::byte>> blob = asset->m_Blob;
        Scripting::GetInstance().Interpret("main", asset->ToString());
        asset->UnloadAsset();
    } 

    Engine::ImGui imgui = Engine::ImGui(window);
    ::ImGui::SetCurrentContext(imgui.GetImGuiContext());
    try {
        Theme theme((std::filesystem::path(getExecutablePath()) / "Themes\\steam.toml").string());
        theme.SetTheme();
    } catch(...) {}

    renderer->SetContext(&app.m_Window);

    ContentBrowser contentBrowser = ContentBrowser();

    bool show_demo_window = true;
    while(!app.WindowShouldClose()) {
        imgui.StartFrame();

        Menu::GetInstance().AddMenuItem("File/Quit", "Ctrl+Q", [window]() {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        });

        ::ImGui::DockSpaceOverViewport(::ImGui::GetMainViewport()->ID);
        ::ImGui::ShowDemoWindow(&show_demo_window);
        contentBrowser.OnImGuiRender();
        
        renderer->ClearBackground(Color::s_Magenta);

        imgui.EndFrame();

        renderer->EndDrawing();
    }

    return 0;
}
