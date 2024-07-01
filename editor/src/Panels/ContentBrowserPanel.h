#pragma once

#include "PanelInterface.h"
#include <filesystem>

class ContentBrowser: PanelInterface {
    public:
        ContentBrowser();
        ~ContentBrowser();

        void OnImGuiRender() override;
    private:
        std::filesystem::path m_BaseDirectory;
        std::filesystem::path m_CurrentDirectory;
};