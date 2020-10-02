#ifndef BFS_H
#define BFS_H
#include <list>
#include "graph.h"
#include "structs.h"
#include <queue>
#include "planner.h"

class BFS : public Planner
{
    Result find_path(Graph graph, Node start, Node goal);
    Node get_min();
    Node visited();
    void write(Graph graph);
    void pop_open();
    void insert_into_open(Node node);
    std::list<Node> reconstruct_path(Node goal);
};

#endif // BFS_H
