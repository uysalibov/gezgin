#pragma once
#include "raylib.h"

namespace gez
{
    namespace AdjList
    {
        typedef struct Point
        {
            int id;
            Point *next;
        } Point;

        extern int size;
        extern int capacity;
        extern Point *array;

        void Init(int size);
        void AddAdj(int pos, int id);
        void Print();
    }
}