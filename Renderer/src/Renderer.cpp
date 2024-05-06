#include "Renderer.h"
#include "OSMJson.h"
#include "Inputs.h"
#include "AdjList.h"
#include "Graph.h"
#include "Dijkstra.h"
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
        // DrawHighways();
        // DrawNodes();
        DrawFromAdjList();
        DrawCursor();
        DrawSelectedNodes();
        DrawDijkstra();
        EndMode2D();
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}

void gez::renderer::DrawSelectedNodes()
{
    for (int i = 0; i < selectedPointsCount; i++)
    {
        Vector2 node = selectedPoints[i];
        DrawCircle(node.x, node.y, 1.f, Color{113, 254, 190, 255});
        DrawText("Closest Node", node.x, node.y, 10, Color{113, 254, 190, 255});
    }
}

void gez::renderer::DrawCursor()
{
    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
    Vector3 closestNode = gez::graph::SelectClosestNode(mousePos);
    DrawCircle(closestNode.x, closestNode.y, 2.f, Color{240, 240, 240, 255});
}

void gez::renderer::DrawNodes()
{
    for (int i = 0; i < fileparser::nodes.size(); i++)
    {
        Vector2 node = fileparser::nodes[i];
        DrawRectangle(node.y + 50, node.x + 50, 1.f, 1.f, Color{113, 254, 190, 255});
        // DrawCircle(node.x + 50, node.y + 50, 1.f, Color{113, 254, 190, 255});
    }
}

void gez::renderer::DrawHighways()
{
    for (int i = 0; i < fileparser::lines.size(); i++)
    {
        Vector4 line = fileparser::lines[i];
        DrawLineEx({line.y + 50, line.x + 50}, {line.w + 50, line.z + 50}, 1.f, Color{110, 110, 110, 255});
    }
}

void gez::renderer::DrawFromAdjList()
{
    for (int i = 0; i < AdjList::capacity; i++)
    {
        AdjList::Point *temp = &AdjList::array[i];
        while (temp != nullptr)
        {
            Vector2 start = fileparser::nodes[i];
            Vector2 end = fileparser::nodes[temp->id];
            DrawLineEx(start, end, 1.f, Color{110, 110, 110, 255});

            temp = temp->next;
        }
    }
}

void gez::renderer::DrawDijkstra()
{
    if (gez::Dijkstra::isRunning)
    {
        gez::Dijkstra::dijkstra();
        for (int i = 0; i < gez::Dijkstra::n; i++)
        {
            if (Dijkstra::spt[i].parent != -1)
            {
                Vector2 start = fileparser::nodes[Dijkstra::spt[i].parent];
                Vector2 end = fileparser::nodes[i];
                DrawLineEx(start, end, 1.f, Color{240, 240, 240, 255});
            }
        }
    }
}

/**
 std::unordered_set<std::string> drawn;
    for (int i = 0; i < AdjList::capacity; i++)
    {
        AdjList::Point *temp = &AdjList::array[i];
        while (temp != nullptr)
        {
            if (temp->next != nullptr)
            {
                std::string key;
                if (temp->id < temp->next->id)
                {
                    key = std::to_string(temp->id) + std::to_string(temp->next->id);
                }
                else
                {
                    key = std::to_string(temp->next->id) + std::to_string(temp->id);
                }
                if (drawn.find(key) == drawn.end())
                {
                    Vector2 start = fileparser::nodes[i];
                    Vector2 end = fileparser::nodes[temp->next->id];
                    DrawLineEx({start.y + 50, start.x + 50}, {end.y + 50, end.x + 50}, 1.f, Color{110, 110, 110, 255});
                    drawn.insert(key);
                }
            }
            temp = temp->next;
        }
    }
*/