#include "input.h"

bool Input::load(const char* fileName)
{
    if (load_graph(fileName))
        std::cout << "Graph loaded" << std::endl;
    else
    {
        std::cout << "Error! Troubles with graph loading!" << std::endl;
        return false;
    }
    if (load_task(fileName))
        std::cout << "Task loaded" << std::endl;
    else
    {
        std::cout << "Error! Troubles with task loading!" << std::endl;
        return false;
    }
    if (load_algorithm_type(fileName))
        std::cout << "Algorithm type loaded" << std::endl;
    else
    {
        std::cout << "Error! Troubles with algorithm type!" << std::endl;
        return false;
    }
    return true;
}

bool Input::load_graph(const char* fileName)
{
    return graph.load_graph(fileName);
}

bool Input::load_task(const char* fileName)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(fileName) != tinyxml2::XMLError::XML_SUCCESS)
    {
        std::cout << "Error opening XML file!" << std::endl;
        return false;
    }
    tinyxml2::XMLElement* root = 0, * element = 0;
    root = doc.FirstChildElement("root");
    element = root->FirstChildElement("graph");
    if (std::strcmp(element->Attribute("type"), "general") == 0)
    {
        element = root->FirstChildElement("task");
        start.id = graph.get_id_by_name(element->Attribute("start.id"));
        goal.id = graph.get_id_by_name(element->Attribute("goal.id"));
    }
    else if (std::strcmp(element->Attribute("type"), "grid") == 0)
    {
        element = root->FirstChildElement("task");
        start.i = element->IntAttribute("start.i");
        start.j = element->IntAttribute("start.j");
        goal.i = element->IntAttribute("goal.i");
        goal.j = element->IntAttribute("goal.j");
        start.id = start.i * root->FirstChildElement("graph")->IntAttribute("width") + start.j;
        goal.id = goal.i * root->FirstChildElement("graph")->IntAttribute("width") + goal.j;
    }
    else
    {
        std::cout << "Wrong graph type! It should by either 'general' or 'grid'" << std::endl;
        return false;
    }
    return true;
}

bool Input::load_algorithm_type(const char* fileName)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(fileName) != tinyxml2::XMLError::XML_SUCCESS)
    {
        std::cout << "Error opening XML file!" << std::endl;
        return false;
    }
    tinyxml2::XMLElement* root = 0, * element = 0;
    root = doc.FirstChildElement("root")->FirstChildElement("algorithm");
    if (std::strcmp(root->Attribute("type"), "dijkstra") == 0 || std::strcmp(root->Attribute("type"), "Dijkstra") == 0)
        algorithm_type = CN_DIJKSTRA;
    else if (std::strcmp(root->Attribute("type"), "bfs") == 0 || std::strcmp(root->Attribute("type"), "BFS") == 0)
        algorithm_type = CN_BFS;
    else if (std::strcmp(root->Attribute("type"), "astar") == 0 || std::strcmp(root->Attribute("type"), "AStar") == 0)
        algorithm_type = CN_ASTAR;
    else
    {
        std::cout << "Wrong algorithm type! Possible values are 'BFS', 'Dijkstra' or 'AStar'. " << std::endl;
        return false;
    }
    return true;
}

void Input::print()
{
    std::cout << "Printing loaded data:" << std::endl;
    if (algorithm_type == CN_BFS)
        std::cout << "Algorithm - BFS" << std::endl;
    if (algorithm_type == CN_DIJKSTRA)
        std::cout << "Algorithm - Dijkstra" << std::endl;
    if (algorithm_type == CN_ASTAR)
        std::cout << "Algorithm - AStar" << std::endl;
    if (start.i >= 0)
        std::cout << "start.i = " << start.i << " start.j =" << start.j << std::endl << "goal.i = " << goal.i << " goal.j = " << goal.j << std::endl;
    else
        std::cout << "start.id = " << graph.get_name_by_id(start.id) << std::endl << "goal.id = " << graph.get_name_by_id(goal.id) << std::endl;
    graph.print();
}
