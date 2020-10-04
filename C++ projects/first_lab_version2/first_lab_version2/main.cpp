#include <iostream>
#include "tinyxml2.h"
#include "input.h"
#include "astar.h"
#include "dijkstra.h"
#include "bfs.h"
#include <fstream>
#include <chrono>

int main(int argc, const char* argv[])
{
    std::string fileName;
    if (argc > 1)
        fileName = argv[1];
    else
        fileName = "grid_example.xml";
    if (argc > 3) // no additional parameters - run the planner in a single-shot mode (изменила < на >, чтобы запускалось competition)
    {
        Input input;
        if (!input.load(fileName.c_str()))
            return 1;
        input.print();
        Planner* planner;
        if (input.algorithm_type == CN_BFS)
            planner = new BFS();
        else if(input.algorithm_type == CN_DIJKSTRA)
            planner = new Dijkstra();
        else
            planner = new AStar();
        Result result = planner->find_path(input.graph, input.start, input.goal);
        if (result.path.empty())
            std::cout << "PATH NOT FOUND!" << std::endl;
        else
        {
            std::cout << "Path cost: " << result.path.back().g << std::endl;
            for (Node n : result.path)
                std::cout << n.id << " ";
            std::cout << "\n";
        }
    }
    else //run the competition
    {
        std::ofstream out("results.txt");
        for (int i = 0; i < 3; i++)
        {
            fileName = "competition/task" + std::to_string(i) + ".xml";
            Input input;
            input.load(fileName.c_str());
            Planner* planner;
            if (input.algorithm_type == CN_BFS)
                planner = new BFS();
            else if(input.algorithm_type == CN_DIJKSTRA)
                planner = new Dijkstra();
            else
                planner = new AStar();
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            Result result = planner->find_path(input.graph, input.start, input.goal);
            end = std::chrono::system_clock::now();
            result.runtime = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / 1e+9;
            out << "Task " << i << ": Cost " << result.cost << " Expanded nodes " << result.expanded << " Generated nodes " << result.generated << " Runtime " << result.runtime << std::endl;
        }
        out.close();
    }

    return 0;
}
