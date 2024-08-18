#pragma once

#ifndef DllExport
#define DllExport __declspec( dllexport )
#endif

#include <GLFW/glfw3.h>

#include "../Core/Window.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "Color.h"

namespace Engine {
    class Renderer {
        public:
            ~Renderer() = default;

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
            void DrawMesh();

        public:
            Window* m_Window;
    };
}