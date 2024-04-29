#include "Renderer.h"
#include "OSMJson.h"
#include "Inputs.h"
#include <iostream>

Camera2D gez::renderer::camera;

void gez::renderer::init(int screenWidth, int screenHeight, const char *title)
{
    camera = {0};
    camera.zoom = 1.0f;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, title);
    MaximizeWindow();
    SetTargetFPS(60);
}

void gez::renderer::run()
{
    while (!WindowShouldClose())
    {
        ProcessInput(&camera);
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(Color{27, 27, 27, 255});
        // DrawText("Hello, World!", 10, 10, 20, Color{110, 110, 110, 255}); // Color{113, 254, 190, 255}
        DrawHighways();
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
}

void gez::renderer::DrawHighways()
{
    for (int i = 0; i < fileparser::lines.size(); i++)
    {
        Vector4 line = fileparser::lines[i];
        DrawLineEx({line.y + 50, GetScreenHeight() / 2 - line.x + 50}, {line.w + 50, GetScreenHeight() / 2 - line.z + 50}, 1.f, Color{110, 110, 110, 255});
    }
}