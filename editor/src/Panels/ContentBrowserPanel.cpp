#include "ContentBrowserPanel.h"

#include <ImGui/Menu.h>

#include <imgui.h>

ContentBrowser::ContentBrowser() {
}

ContentBrowser::~ContentBrowser() {
}

void ContentBrowser::OnImGuiRender() {
    Engine::Menu::GetInstance().AddMenuItem("Panels/Content Browser", "", [this]() {
        this->ToggleWindow();
    });

    if(this->m_WindowIsOpen) {
        ImGui::Begin("Content Browser");

        ImGui::End();
    }
}