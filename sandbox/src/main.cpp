#include "Renderer/OpenGL/OpenGL.h"
#include <Core/Application.h>

#include <Renderer/Color.h>

using namespace Engine;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    Application app(screenWidth, screenHeight, "Sandbox");
    OpenGL* renderer = &app.m_Renderer;

    renderer->SetContext(&app.m_Window);

    while(!app.WindowShouldClose()) {
        renderer->ClearBackground(Color::s_Purple);
        renderer->EndDrawing();
    }

    return 0;
}