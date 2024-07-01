#include "ContentBrowserPanel.h"
#include "../Menu/Menu.h"

#include <imgui.h>

ContentBrowser::ContentBrowser() {
}

ContentBrowser::~ContentBrowser() {
}

void ContentBrowser::OnImGuiRender() {
    Menu::GetInstance().AddMenuItem("Panels/Content Browser", "", [this]() {
        this->ToggleWindow();
    });

    if(this->m_WindowIsOpen) {
        ImGui::Begin("Content Browser");

        ImGui::End();
    }
}