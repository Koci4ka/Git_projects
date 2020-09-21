#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <list>
#include <algorithm>
#include "graph.h"
#include "structs.h"
#include "planner.h"

class Dijkstra : public Planner
{
    std::list<Node> find_path(Graph graph, Node start, Node goal);
    Node get_min();
    void write(Graph graph);
    void pop_open();
    void insert_into_open(Node node);
    std::list<Node> reconstruct_path(Node goal);
};

#endif // DIJKSTRA_H
