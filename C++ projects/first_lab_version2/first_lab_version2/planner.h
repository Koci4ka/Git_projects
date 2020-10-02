#ifndef PLANNER_H
#define PLANNER_H
#include <list>
#include <unordered_map>
#include "structs.h"
#include "graph.h"

class Planner
{
public:
    virtual Result find_path(Graph graph, Node start, Node goal);
    Result result;
protected:
    std::list<Node> reconstruct_path(Node goal); //восстанавливает путь
    Node get_min(); //находит элемент с минимальным g-значением
    void pop_open(); //удаляет элемент из open
    bool in_closed(Node node); //проверяет наличие вершины в списке CLOSED
    bool in_open(Node node); //проверяет наличие веришины в списке OPEN
    void insert_into_open(Node node); //вставить вершину в список OPEN
    void insert_into_closed(Node node); //вставить вершину в список CLOSED
    std::list<Node> open;
    std::unordered_map<int, Node> closed;
};

#endif // PLANNER_H
