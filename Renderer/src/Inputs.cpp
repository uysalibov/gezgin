#include "Inputs.h"
#include "raymath.h"

namespace gez
{
    namespace renderer
    {
        void ProcessInput(Camera2D *camera)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {
                Vector2 delta = GetMouseDelta();
                delta = Vector2Scale(delta, -1.0f / camera->zoom);

                camera->target = Vector2Add(camera->target, delta);
            }

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
        }
    }
}