#pragma once

#include <ImGui/PanelInterface.h>
#include <filesystem>

class ContentBrowser: Engine::PanelInterface {
    public:
        ContentBrowser();
        ~ContentBrowser();

        void OnImGuiRender() override;
    private:
        std::filesystem::path m_BaseDirectory;
        std::filesystem::path m_CurrentDirectory;
};