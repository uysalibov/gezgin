#include "Renderer.h"
#include "OSMJson.h"

int main()
{
    gez::renderer::init(1080, 720, "Gezgin Pathfinding Visualizer");

    gez::renderer::run();
    return 0;
}