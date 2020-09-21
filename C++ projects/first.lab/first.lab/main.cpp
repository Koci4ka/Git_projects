#include <iostream>
#include "tinyxml2.h"
#include "input.h"
#include "astar.h"
#include "dijkstra.h"
#include "bfs.h"

int main(int argc, const char* argv[])
{
    std::string fileName;
    if (argc > 1)
        fileName = argv[1];
    else
        fileName = "grid_example.xml";
    Input input;
    if (!input.load(fileName.c_str()))
        return 1;
    input.print();
    Planner* planner;
    if (input.algorithm_type == CN_BFS)
        planner = new BFS();
    else if (input.algorithm_type == CN_DIJKSTRA)
        planner = new Dijkstra();
    else
        planner = new AStar();
    std::list<Node> path = planner->find_path(input.graph, input.start, input.goal);
    if (path.empty())
        std::cout << "PATH NOT FOUND!" << std::endl;
    else
    {
        std::cout << "Path cost: " << path.back().g << std::endl;
        Graph gph;
        gph = input.graph;
        if (gph.get_commectedness() == 0) {
            std::cout << "\n";
            for (Node g : path) {
                std::cout << gph.get_name_by_id(g.id) << " " << g.g << " ";
                std::cout << "\n";
            }
        }
        else {
            std::cout << "i;j - g\n";
            std::cout << "_______\n";
            std::cout << "\n";
            for (Node g : path) {
                std::cout << g.id / 10 << ";" << g.id % 10 << " - " << g.g << " ";
                std::cout << "\n";
            }
        }
    }

    return 0;
}
