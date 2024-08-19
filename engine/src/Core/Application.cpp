#include "Application.h"
#include "SceneManager.h"
#include <filesystem>

namespace Engine {
    Application::Application(): m_AssetDatabase((std::filesystem::current_path() / "assets").string()), m_SceneManager() {
    }
}