#include "Renderer/RendererAPI.h"
#include <Core/Application.h>

#include <Renderer/Color.h>

using namespace Engine;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    Application* app = new Application(screenWidth, screenHeight, "Sandbox");
    RendererAPI* renderer = app->m_Renderer;

    renderer->SetContext(app->m_Window);

    while(!app->WindowShouldClose()) {
        renderer->ClearBackground(Color(255, 235, 4, 255));

        renderer->EndDrawing();
    }

    return 0;
}