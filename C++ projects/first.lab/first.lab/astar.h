#ifndef ASTAR_H
#define ASTAR_H
#include <list>
#include "graph.h"
#include "structs.h"
#include "planner.h"
#include <algorithm>
//���������� A*
//1) ���������� ����� Planner +
//2) ���������� ������ �������, ����� ��� find_path, insert_into_open
//3) ���������� ������� ��� ������� ������������� ������� � ������ ��������� �����

class AStar : public Planner
{
public:
    std::list<Node> find_path(Graph graph, Node start, Node goal);
    void insert_into_open(Node node);
    Node get_min();
    void pop_open();
    std::list<Node> reconstruct_path(Node goal);
    float h_value(Node current, Node goal, Graph graph);
    void write(Graph graph);
};

#endif // ASTAR_H
