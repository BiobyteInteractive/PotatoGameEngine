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

#ifdef _WIN32
    #include <Windows.h>
    #include <winbase.h>
    #include <shobjidl.h> 
#endif

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
        while(projectPath.empty() || !std::filesystem::path(projectPath).has_filename()) {
            HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
            COINIT_DISABLE_OLE1DDE);
            if (SUCCEEDED(hr))
            {
                IFileOpenDialog *pFileOpen;

                // Create the FileOpenDialog object.
                hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, 
                        IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

                if (SUCCEEDED(hr))
                {
                    // Show the Open dialog box.
                    hr = pFileOpen->Show(NULL);

                    // Get the file name from the dialog box.
                    if (SUCCEEDED(hr))
                    {
                        IShellItem *pItem;
                        hr = pFileOpen->GetResult(&pItem);
                        if (SUCCEEDED(hr))
                        {
                            PWSTR pszFilePath;
                            hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                            // Display the file name to the user.
                            if (SUCCEEDED(hr))
                            {
                                if (pszFilePath == nullptr) {
                                    projectPath = "";
                                }

                                // Get the length of the resulting string
                                int size_needed = WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, nullptr, 0, nullptr, nullptr);

                                // Allocate a string with the needed size
                                std::string strTo(size_needed, 0);

                                // Perform the conversion
                                WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, &strTo[0], size_needed, nullptr, nullptr);

                                // Remove the null terminator that WideCharToMultiByte adds
                                strTo.resize(size_needed - 1);

                                projectPath = strTo;
                            }
                            pItem->Release();
                        }
                    }
                    pFileOpen->Release();
                }
                CoUninitialize();
            }
        }
    } else {
        projectPath = std::string(argv[1]);
    }
    std::filesystem::current_path(std::filesystem::path(projectPath).remove_filename().string());

    const int screenWidth = 800;
    const int screenHeight = 450;

    Application app(screenWidth, screenHeight, (char*)"Paragon Game Engine");
    GLFWwindow* window = app.GetWindow();

    AssetDatabase asset_db((std::filesystem::current_path() / "assets").string());
    
    std::vector<size_t> scriptIDs = asset_db.SelectAssets("SELECT * FROM assets WHERE EXTENSION like '.wren' AND DIRECTORY like '%editor%'", 0);
    for(const size_t& id : scriptIDs) {
        std::shared_ptr<Asset> asset = asset_db.GetAssetByID(id);
        asset->LoadAssetSync();

        std::shared_ptr<std::vector<std::byte>> blob = asset->m_Blob;
        Scripting::GetInstance().Interpret("main", asset->ToString());
        asset->UnloadAsset();
    } 

    const char* glsl_version = "#version 330";
    ::IMGUI_CHECKVERSION();
    ::ImGui::CreateContext();
    ImGuiIO& io = ::ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ::ImGui::StyleColorsDark();

    Engine::ImGui::SetImGuiContext(::ImGui::GetCurrentContext());
    
    try {
        Theme theme((std::filesystem::path(getExecutablePath()) / "Themes\\steam.toml").string());
        theme.SetTheme();
    } catch(...) {}

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    OpenGL* renderer = &app.m_Renderer;

    renderer->SetContext(&app.m_Window);

    ContentBrowser contentBrowser = ContentBrowser();

    bool show_demo_window = true;
    while(!app.WindowShouldClose()) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ::ImGui::NewFrame();

            Menu::GetInstance().AddMenuItem("File/Quit", "Ctrl+Q", [window]() {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            });

            ::ImGui::DockSpaceOverViewport(::ImGui::GetMainViewport()->ID);
            ::ImGui::ShowDemoWindow(&show_demo_window);
            contentBrowser.OnImGuiRender();
            
            ::ImGui::Render();
            renderer->ClearBackground(Color::s_Magenta);

            ImGui_ImplOpenGL3_RenderDrawData(::ImGui::GetDrawData());

            // Update and Render additional Platform Windows
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ::ImGui::UpdatePlatformWindows();
                ::ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

        renderer->EndDrawing();
    }

    return 0;
}
