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
    std::list<Node> reconstruct_path(Node goal); //��������������� ����
    Node get_min(); //������� ������� � ����������� g-���������
    void pop_open(); //������� ������� �� open
    bool in_closed(Node node); //��������� ������� ������� � ������ CLOSED
    bool in_open(Node node); //��������� ������� �������� � ������ OPEN
    void insert_into_open(Node node); //�������� ������� � ������ OPEN
    void insert_into_closed(Node node); //�������� ������� � ������ CLOSED
    std::list<Node> open;
    std::unordered_map<int, Node> closed;
};

#endif // PLANNER_H
