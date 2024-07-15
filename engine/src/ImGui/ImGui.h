#pragma once

#ifndef DllExport
#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif
#endif

#include <imgui.h>
#include <GLFW/glfw3.h>

#include <functional>

namespace Engine {
    typedef std::function<void()> Function;

    class DllExport ImGui {
        public:
            ImGui(GLFWwindow* window);
            ~ImGui() = default;

            void OnImGuiRender(Function function);

            static void SetImGuiContext(::ImGuiContext* ctx);
            static ::ImGuiContext* GetImGuiContext();

            void StartFrame();
            void EndFrame();
    };
}
