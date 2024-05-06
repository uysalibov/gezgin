#include "Dijkstra.h"
#include <cmath>
#include "OSMJson.h"

gez::Dijkstra::SPT *gez::Dijkstra::spt;
std::vector<int> gez::Dijkstra::stepList;
int gez::Dijkstra::n = 0;
float gez::Dijkstra::frameTime = 0;
bool gez::Dijkstra::isRunning = false;

void gez::Dijkstra::init(int n)
{
    gez::Dijkstra::n = n;
    spt = new SPT[n];
    for (int i = 0; i < n; i++)
    {
        spt[i].weight = INFINITY;
        spt[i].parent = -1;
        spt[i].visited = false;
    }
    stepList.clear();
}

void gez::Dijkstra::start(int start)
{
    isRunning = true;
    spt[start].weight = 0;
    spt[start].visited = true;
    gez::AdjList::Point *temp = &gez::AdjList::array[start];

    if (temp->id != -1)
    {
        spt[temp->id].weight = sqrt(pow(gez::fileparser::nodes[start].x - gez::fileparser::nodes[temp->id].x, 2) + pow(gez::fileparser::nodes[start].y - gez::fileparser::nodes[temp->id].y, 2));
        spt[temp->id].parent = start;
        stepList.push_back(temp->id);
    }

    while (temp->next != nullptr)
    {
        temp = temp->next;
        spt[temp->id].weight = sqrt(pow(gez::fileparser::nodes[start].x - gez::fileparser::nodes[temp->id].x, 2) + pow(gez::fileparser::nodes[start].y - gez::fileparser::nodes[temp->id].y, 2));
        spt[temp->id].parent = start;
        stepList.push_back(temp->id);
    }
}

void gez::Dijkstra::dijkstra()
{
    std::vector<int> temp;
    for (size_t i = 0; i < stepList.size(); i++)
    {
        // check adj nodes is visited
        if (!spt[stepList[i]].visited)
        {
            spt[stepList[i]].visited = true;
            gez::AdjList::Point *tempAdj = &gez::AdjList::array[stepList[i]];

            if (tempAdj->id != -1)
            {
                float weight = sqrt(pow(gez::fileparser::nodes[stepList[i]].x - gez::fileparser::nodes[tempAdj->id].x, 2) + pow(gez::fileparser::nodes[stepList[i]].y - gez::fileparser::nodes[tempAdj->id].y, 2));
                if (spt[tempAdj->id].weight > spt[stepList[i]].weight + weight)
                {
                    spt[tempAdj->id].weight = spt[stepList[i]].weight + weight;
                    spt[tempAdj->id].parent = stepList[i];
                    temp.push_back(tempAdj->id);
                }
            }

            while (tempAdj->next != nullptr)
            {
                tempAdj = tempAdj->next;
                float weight = sqrt(pow(gez::fileparser::nodes[stepList[i]].x - gez::fileparser::nodes[tempAdj->id].x, 2) + pow(gez::fileparser::nodes[stepList[i]].y - gez::fileparser::nodes[tempAdj->id].y, 2));
                if (spt[tempAdj->id].weight > spt[stepList[i]].weight + weight)
                {
                    spt[tempAdj->id].weight = spt[stepList[i]].weight + weight;
                    spt[tempAdj->id].parent = stepList[i];
                    temp.push_back(tempAdj->id);
                }
            }
        }
    }
    stepList = temp;
}
