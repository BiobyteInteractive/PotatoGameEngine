#pragma once

#include <functional>
#include <string>
#include <vector>

#define DllExport __declspec( dllexport )

namespace Engine {
    typedef std::function<void()> MenuItemFn;

    class DllExport Menu {
        public:
            static Menu& GetInstance() {
                static Menu instance;
                return instance;
            }

            Menu(const Menu&) = delete;
            Menu& operator=(const Menu&) = delete;

            static void AddMenuItem(std::string menuItem, std::string shortcut, MenuItemFn function);
        private:
            Menu() = default;
            ~Menu() = default;

            friend std::vector<std::string> split(const std::string& str, char delimiter);
    };
}