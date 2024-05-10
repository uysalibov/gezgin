#pragma once
#include "raylib.h"

namespace gez
{
    namespace NodeAnim
    {
        typedef struct NodeAnimItem
        {
            int id;
            Color color;
            float radius;
            float duration;
            bool isStarted;
            bool isFinished;
        } NodeAnimItem;

        extern NodeAnimItem nodeAnimList[2];

        void AddNode(int id, Color color, float duration);
        void UpdateNode(float deltaTime);
    }
}