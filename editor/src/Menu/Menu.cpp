#include "Menu.h"

#include <sstream>
#include <string>
#include <vector>

#include "imgui.h"

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::string token;
    std::stringstream ss(str);

    // Use getline to split the string by the delimiter
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

void Menu::AddMenuItem(std::string menuItem, std::string shortcut, MenuItemFn function) {
    // Split the menu path
    std::vector<std::string> menuPath = split(menuItem, '/');
    
    std::vector<bool> open(menuPath.size(), false);

    ImGui::BeginMainMenuBar();

    // Traverse the menu path
    for (int i = 0; i < menuPath.size(); ++i) {
        if (i < menuPath.size() - 1) {
            open[i] = ImGui::BeginMenu(menuPath[i].c_str());
            if (!open[i]) {
                // If a menu fails to open, stop processing further
                break;
            }
        } else {
            // For the last item in the path, create a MenuItem
            if (ImGui::MenuItem(menuPath[i].c_str(), shortcut.c_str())) {
                function();
            }
        }
    }

    // Close all opened menus
    for (int i = menuPath.size() - 1; i >= 0; --i) {
        if (open[i]) {
            ImGui::EndMenu();
        }
    }

    ImGui::EndMainMenuBar();
}