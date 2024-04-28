#include "renderer.h"
#include "OSMJson.h"

int main()
{
    gez::renderer::init(1080, 720, "Gezgin Pathfinding Visualizer");

    gez::fileparser::ReadFile("./Maps/simpleIST.json");
    // gez::fileparser::PrintData();

    gez::renderer::run();
    return 0;
}