#ifndef INPUT_H
#define INPUT_H
#include "graph.h"
#include "tinyxml2.h"
#define CN_BFS      1
#define CN_DIJKSTRA 2
#define CN_ASTAR    3


class Input
{
public:
    bool load(const char* fileName);
    bool load_task(const char* fileName);
    bool load_graph(const char* fileName);
    bool load_algorithm_type(const char* fileName);
    void print();
    Graph graph;
    Node start;
    Node goal;
    int algorithm_type;
};

#endif // INPUT_H
