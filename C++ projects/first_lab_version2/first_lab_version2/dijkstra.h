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
    Node get_min();
    void write(Graph graph);
    void pop_open();
    void insert_into_open(Node node);
    std::list<Node> reconstruct_path(Node goal);

    struct CustomCompare
    {
        bool operator()(const std::pair<int, Node>& lhs, const std::pair<int, Node>& rhs)
        {
            return lhs.first > rhs.first;
        }
    };
};

#endif // DIJKSTRA_H
