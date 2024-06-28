#pragma once

#include <functional>
#include <string>
#include <vector>

typedef std::function<void()> MenuItemFn;

class Menu {
    public:
        static Menu& GetInstance() {
            static Menu instance;
            return instance;
        }

        Menu(const Menu&) = delete;
        Menu& operator=(const Menu&) = delete;

        void AddMenuItem(std::string menuItem, std::string shortcut, MenuItemFn function);
    private:
        Menu() = default;
        ~Menu() = default;

        friend std::vector<std::string> split(const std::string& str, char delimiter);
};