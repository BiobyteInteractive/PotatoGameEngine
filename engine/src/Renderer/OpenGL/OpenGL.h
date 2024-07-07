#pragma once

#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif

#include "../RendererAPI.h"

namespace Engine {
    class DllExport OpenGL: public virtual RendererAPI {
        public:
            OpenGL() = default;
            ~OpenGL() = default;

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
    };
}