#include "Renderer.h"
#include "OSMJson.h"
#include "Inputs.h"
#include "AdjList.h"
#include "Graph.h"
#include "Dijkstra.h"
#include "NodeAnim.h"
#include <iostream>

Camera2D gez::renderer::camera;
RenderTexture2D gez::renderer::target;
Vector4 *gez::renderer::bounds;

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
    InitMapTexture();
    while (!WindowShouldClose())
    {
        ProcessInput(&camera);
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(Color{27, 27, 27, 255});
        DrawTexturePro(target.texture, {0, 0, (float)target.texture.width, (float)-target.texture.height}, {0, 0, (float)GetScreenWidth(), (float)GetScreenWidth()}, {0, 0}, 0, WHITE);
        gez::NodeAnim::UpdateNode(GetFrameTime());

        DrawCursor();
        DrawDijkstra();
        DrawSelectedNodes();
        EndMode2D();
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}

void gez::renderer::InitMapTexture()
{
    int scale = 4;
    target = LoadRenderTexture(GetScreenWidth() * scale, GetScreenWidth() * scale);
    BeginTextureMode(target);
    ClearBackground(Color{27, 27, 27, 255});
    DrawFromAdjList(scale);
    EndTextureMode();

    bounds = fileparser::GetBounds();
    std::cout << "Bounds: " << bounds->x << " " << bounds->y << " " << bounds->z << " " << bounds->w << std::endl;
}

void gez::renderer::DrawSelectedNodes()
{
    for (int i = 0; i < selectedPointsCount; i++)
    {
        Vector3 node = selectedPoints[i];
        if (gez::NodeAnim::nodeAnimList[i].isStarted || gez::NodeAnim::nodeAnimList[i].isFinished)
        {
            DrawCircle(node.x, node.y, gez::NodeAnim::nodeAnimList[i].radius, gez::NodeAnim::nodeAnimList[i].color);
        }
        // DrawCircle(node.x, node.y, 1.f, Color{113, 254, 190, 255});
        if (i == 0)
        {
            DrawText("Start Node", node.x, node.y + 5, 15, Color{113, 254, 190, 255});
        }
        else if (i == 1)
        {
            DrawText("End Node", node.x, node.y + 5, 15, Color{113, 254, 190, 255});
        }
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

void gez::renderer::DrawFromAdjList(int scale)
{
    for (int i = 0; i < AdjList::capacity; i++)
    {
        AdjList::Point *temp = &AdjList::array[i];
        while (temp != nullptr)
        {
            Vector2 start = {fileparser::nodes[i].x * scale, fileparser::nodes[i].y * scale};
            Vector2 end = {fileparser::nodes[temp->id].x * scale, fileparser::nodes[temp->id].y * scale};
            DrawLineEx(start, end, scale, Color{110, 110, 110, 255});

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

    // draw path from start to end
    if (gez::Dijkstra::isFinished)
    {
        int endId = gez::Dijkstra::startStop[1];
        int parent = gez::Dijkstra::spt[endId].parent;
        while (parent != -1)
        {
            Vector2 start = fileparser::nodes[parent];
            Vector2 end = fileparser::nodes[endId];
            DrawLineEx(start, end, 1.f, Color{240, 0, 0, 255});
            endId = parent;
            parent = gez::Dijkstra::spt[endId].parent;
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