#include "Renderer.h"
#include "OSMJson.h"
#include <iostream>

void gez::renderer::init(int screenWidth, int screenHeight, const char *title)
{
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);
}

void gez::renderer::run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{27, 27, 27, 255});
        // DrawText("Hello, World!", 10, 10, 20, Color{110, 110, 110, 255});
        DrawHighways();
        EndDrawing();
    }
    CloseWindow();
}

void gez::renderer::DrawHighways()
{
    for (int i = 0; i < fileparser::lines.size(); i++)
    {
        Vector4 line = fileparser::lines[i];
        DrawLineEx({line.y + 50, line.x + 50}, {line.w + 50, line.z + 50}, 5.f, Color{110, 110, 110, 255});
    }
}