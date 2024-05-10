#include "NodeAnim.h"

gez::NodeAnim::NodeAnimItem gez::NodeAnim::nodeAnimList[2];

void gez::NodeAnim::AddNode(int id, Color color, float duration)
{
    nodeAnimList[id].id = id;
    nodeAnimList[id].color = color;
    nodeAnimList[id].radius = 0.1f;
    nodeAnimList[id].duration = duration;
    nodeAnimList[id].isStarted = true;
    nodeAnimList[id].isFinished = false;
}

void gez::NodeAnim::UpdateNode(float deltaTime)
{

    for (int i = 0; i < 2; i++)
    {
        if (nodeAnimList[i].isStarted)
        {
            // increase radius by time
            if (nodeAnimList[i].duration > 0)
            {
                nodeAnimList[i].radius += deltaTime * 10;
                nodeAnimList[i].duration -= deltaTime;
            }
            else
            {
                nodeAnimList[i].isFinished = true;
                nodeAnimList[i].isStarted = false;
            }
        }
    }
}