#include "Graph.h"
#include "OSMJson.h"

Vector3 gez::graph::SelectClosestNode(Vector2 cursor)
{
    Vector2 closestNode = fileparser::nodes[0];
    int id = 0;
    float closestDistance = sqrt(pow(cursor.x - closestNode.x, 2) + pow(cursor.y - closestNode.y, 2));
    for (int i = 1; i < fileparser::nodes.size(); i++)
    {
        Vector2 node = fileparser::nodes[i];
        float distance = sqrt(pow(cursor.x - node.x, 2) + pow(cursor.y - node.y, 2));
        if (distance < closestDistance)
        {
            closestDistance = distance;
            closestNode = node;
            id = i;
        }
    }
    return {closestNode.x, closestNode.y, (float)id};
}