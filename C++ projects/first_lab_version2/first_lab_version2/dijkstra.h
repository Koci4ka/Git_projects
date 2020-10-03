#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <list>
#include <algorithm>
#include "graph.h"
#include "structs.h"
#include "planner.h"
#include <queue>


class Dijkstra : public Planner
{
    Result find_path(Graph graph, Node start, Node goal);
    Result reconstruct_path(Node goal);

    struct CustomCompare
    {
        bool operator()(const std::pair<float, Node*>& lhs, const std::pair<float, Node*>& rhs)
        {
            return lhs.first > rhs.first;
        }
    };
};

#endif // DIJKSTRA_H
