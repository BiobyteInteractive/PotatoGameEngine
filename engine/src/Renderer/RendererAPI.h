/*
    The RendererAPI should be an interface to be implemented by the different APIs (OpenGL, Vulkan, DirectX, Metal, WebGL, WebGPU).
*/

#pragma once

#define DllExport __declspec( dllexport )

#include <GLFW/glfw3.h>

#include "../Core/Window.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "Color.h"

namespace Engine {
    class DllExport RendererAPI {
        public:
            enum class API {
                None   = 0,
                OpenGL = 1,
                Vulkan = 2,
                WebGPU = 3,
                WebGL  = 4,
                DX12   = 5,
                Metal  = 6
            };
        public:
            ~RendererAPI() = default;

            void ClearBackground(Color color);
            void EndDrawing();

            void SetContext(Window* window);

            // ImGui Rendering Calls
            void RenderImGuiDrawData();

            // 2D Rendering Calls
            void DrawPoint(Vector2 point, Color color);
            void DrawLine(Vector2 start, Vector2 end, Color color);
            void DrawQuad();

            // 3D Rendering Calls
            void DrawPoint(Vector3 point, Color color);
            void DrawLine(Vector3 start, Vector3 end, Color color);

        private:
            Window* m_Window;
        
        private:
            static API s_API;
    };
}