#pragma once

#define DllExport __declspec( dllexport )

#include "Theme.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <GLFW/glfw3.h>

#include <functional>

namespace Engine {
    typedef std::function<void()> Function;

    class DllExport ImGui {
        public:
            ImGui(GLFWwindow* window, Theme* theme);
            ~ImGui() = default;

            void OnImGuiRender(Function function);

            static void SetImGuiContext(::ImGuiContext* ctx);
            static ::ImGuiContext* GetImGuiContext();
    };
}
