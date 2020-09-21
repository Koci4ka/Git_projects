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
    std::vector<std::string> names; //структура для хранения "имен" вершин, т.е. id из входного файла
    std::vector<std::list<std::pair<int, float>>> nodes; //структура для хранения "обычного" графа
    std::vector<std::vector<int>> grid; //структура для хранения графа регулярной декомпозии (он же сетка, грид и т.д.)
    int connectedness; //связность грида
};

#endif // GRAPH_H
