#include "AdjList.h"
#include <iostream>

int gez::AdjList::size = 0;
int gez::AdjList::capacity = 0;
gez::AdjList::Point *gez::AdjList::array = nullptr;

void gez::AdjList::Init(int size)
{
    capacity = size;
    array = new Point[size];
    for (int i = 0; i < size; i++)
    {
        array[i].id = -1;
        array[i].next = nullptr;
    }
}

void gez::AdjList::AddAdj(int pos, int id)
{
    size++;
    if (array[pos].id == -1)
    {
        array[pos].id = id;
    }
    else
    {
        Point *temp = &array[pos];
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = new Point;
        temp->next->id = id;
        temp->next->next = nullptr;
    }
}

void gez::AdjList::Print()
{
    for (int i = 0; i < capacity; i++)
    {
        std::cout << "Node " << i << ": ";
        Point *temp = &array[i];
        while (temp != nullptr)
        {
            std::cout << temp->id << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}
