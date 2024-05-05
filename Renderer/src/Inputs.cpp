#include "Inputs.h"
#include "raymath.h"
#include "Graph.h"

Vector2 gez::renderer::selectedPoints[2];
int gez::renderer::selectedPointsCount = 0;

namespace gez
{
    namespace renderer
    {
        void ProcessInput(Camera2D *camera)
        {
            // Dragging the camera
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {
                Vector2 delta = GetMouseDelta();
                delta = Vector2Scale(delta, -1.0f / camera->zoom);

                camera->target = Vector2Add(camera->target, delta);
            }

            // Zooming the camera
            float wheel = GetMouseWheelMove();
            if (wheel != 0)
            {
                Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *camera);

                camera->offset = GetMousePosition();

                camera->target = mouseWorldPos;

                const float zoomIncrement = 0.125f;

                camera->zoom += wheel * zoomIncrement;
                if (camera->zoom < zoomIncrement)
                {
                    camera->zoom = zoomIncrement;
                }
            }

            // Selecting points
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
                Vector2 closestNode = gez::graph::SelectClosestNode(mousePos);
                if (selectedPointsCount < 2)
                {
                    selectedPoints[selectedPointsCount] = closestNode;
                    selectedPointsCount++;
                }
                else
                {
                    selectedPointsCount = 0;
                }
            }
        }
    }
}