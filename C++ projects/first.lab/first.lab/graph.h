#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <math.h>
#include "tinyxml2.h"
#include "structs.h"

class Graph
{
public:
    Graph() { connectedness = 0; }
    bool load_graph(const char* fileName);
    float get_cost(int id1, int id2);
    void print();
    std::list<Node> get_neighbors(Node current);
    int get_id_by_name(std::string name);
    std::string get_name_by_id(int id);
    int get_commectedness();
private:
    std::vector<std::string> names; //��������� ��� �������� "����" ������, �.�. id �� �������� �����
    std::vector<std::list<std::pair<int, float>>> nodes; //��������� ��� �������� "��������" �����
    std::vector<std::vector<int>> grid; //��������� ��� �������� ����� ���������� ���������� (�� �� �����, ���� � �.�.)
    int connectedness; //��������� �����
};

#endif // GRAPH_H
