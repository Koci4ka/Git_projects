#ifndef ASTAR_H
#define ASTAR_H
#include <list>
#include "graph.h"
#include "structs.h"
#include "planner.h"
#include <algorithm>
#include <queue>
//���������� A*
//1) ���������� ����� Planner
//2) ���������� ������ �������, ����� ��� find_path, insert_into_open
//3) ���������� ������� ��� ������� ������������� ������� � ������ ��������� �����

class AStar : public Planner
{
public:
    Result find_path(Graph graph, Node start, Node goal);
    Result reconstruct_path(Node goal);
    float h_value(Node current, Node goal, Graph graph);
    struct CustomCompare
    {
        bool operator()(const std::pair<float, Node*>& lhs, const std::pair<float, Node*>& rhs)
        {
            return lhs.first > rhs.first;
        }
    };
};

#endif // ASTAR_H