#include "graph.h"

bool Graph::load_graph(const char* fileName)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(fileName) != tinyxml2::XMLError::XML_SUCCESS)
    {
        std::cout << "Error opening XML file!" << std::endl;
        return false;
    }
    tinyxml2::XMLElement* root = 0, * element = 0;
    root = doc.FirstChildElement("root")->FirstChildElement("graph");
    std::string type = root->Attribute("type");
    if (type == "general")
    {
        std::map<std::string, int> ids;
        for (element = root->FirstChildElement("node"); element; element = element->NextSiblingElement("node"))
        {
            names.push_back(element->Attribute("id"));
            nodes.push_back(std::list<std::pair<int, float>>());
            ids.insert(std::make_pair(names.back(), names.size() - 1));
        }
        for (element = root->FirstChildElement("edge"); element; element = element->NextSiblingElement("edge"))
        {
            std::string source = element->Attribute("source");
            std::string target = element->Attribute("target");
            float weight = element->FloatAttribute("weight");
            nodes[ids[source]].push_back(std::make_pair(ids[target], weight));
        }
    }
    if (type == "grid")
    {
        int width = root->IntAttribute("width");
        int height = root->IntAttribute("height");
        if (width <= 0 || height <= 0)
        {
            std::cout << "Wrong grid size!" << std::endl;
            return false;
        }
        connectedness = root->IntAttribute("connectedness");
        if (connectedness != 4 && connectedness != 8)
        {
            std::cout << "Wrong connectedness value! It should be either 4 or 8!" << std::endl;
            return false;
        }
        int grid_i(0), grid_j(0);
        element = root->FirstChildElement();
        grid.resize(height);
        for (int i = 0; i < width; i++)
            grid[i].resize(width, 0);
        while (grid_i < width)
        {
            if (!element)
            {
                std::cout << "Error! Not enough 'row' tags inside 'graph' tag." << std::endl;
                return false;
            }
            std::string str = element->GetText();
            std::vector<std::string> elems;
            std::stringstream ss(str), stream;
            std::string item;
            while (std::getline(ss, item, ' '))
                elems.push_back(item);
            grid_j = 0;
            int val;
            if (elems.size() > 0)
                for (grid_j = 0; grid_j < height; ++grid_j)
                {
                    if (grid_j == int(elems.size()))
                        break;
                    stream.str("");
                    stream.clear();
                    stream << elems[grid_j];
                    stream >> val;
                    grid[grid_i][grid_j] = val;
                }

            if (grid_j != height)
            {
                std::cout << "Invalid value in the " << grid_i + 1 << " row." << std::endl;
                return false;
            }
            ++grid_i;
            element = element->NextSiblingElement();
        }
        nodes.resize(width * height);

    }
    return true;
}

void Graph::print()
{
    if (connectedness == 4 || connectedness == 8)
    {
        std::cout << "Graph type - grid" << std::endl << "Width = " << grid[0].size() << std::endl << "Height = " << grid.size() << std::endl << "Connectedness=" << connectedness << std::endl;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
                std::cout << grid[i][j] << " ";
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "Graph type - general" << std::endl;
        for (int i = 0; i < nodes.size(); i++)
        {
            std::cout << "Node " << names[i] << ": ";
            for (std::list<std::pair<int, float>>::iterator it = nodes[i].begin(); it != nodes[i].end(); it++)
                std::cout << "(" << names[it->first] << "," << it->second << "); ";
            std::cout << std::endl;
        }
    }
    return;
}

std::list<Node> Graph::get_neighbors(Node current)
{
    Node neighbor;
    std::list<Node> neighbors;
    if (connectedness == 4 || connectedness == 8)
    {
        int width(grid[0].size()), height(grid.size());
        if (current.i > 0)
            if (grid[current.i - 1][current.j] == 0)
                neighbors.push_back(Node((current.i - 1) * width + current.j, nullptr, current.i - 1, current.j));
        if (current.i + 1 < width)
            if (grid[current.i + 1][current.j] == 0)
                neighbors.push_back(Node((current.i + 1) * width + current.j, nullptr, current.i + 1, current.j));
        if (current.j > 0)
            if (grid[current.i][current.j - 1] == 0)
                neighbors.push_back(Node(current.i * width + current.j - 1, nullptr, current.i, current.j - 1));
        if (current.j + 1 < height)
            if (grid[current.i][current.j + 1] == 0)
                neighbors.push_back(Node(current.i * width + current.j + 1, nullptr, current.i, current.j + 1));
        if (connectedness == 8)
        {
            //нужно добавить еще 4 вершины (смежные по диагонали)
        }
    }
    else
    {
        for (std::list<std::pair<int, float>>::iterator it = nodes[current.id].begin(); it != nodes[current.id].end(); it++)
            neighbors.push_back(Node(it->first));
    }

    return neighbors;
}

float Graph::get_cost(int id1, int id2)
{
    if (connectedness == 4)
    {
        if (abs(id1 - id2) == 1 || abs(id1 - id2) == grid[0].size())
            return 1.0;
        else
            return -1;
    }
    else if (connectedness == 8)
    {
        if (abs(id1 - id2) == 1 || abs(id1 - id2) == grid[0].size())
            return 1.0;
        else if (abs(id1 - id2) == grid[0].size() - 1 || abs(id1 - id2) == grid[0].size() + 1)
            return sqrt(2.0);
        else
            return -1;
    }
    else
    {
        for (std::list<std::pair<int, float>>::iterator it = nodes[id1].begin(); it != nodes[id1].end(); it++)
            if (it->first == id2)
                return it->second;
        return -1;
    }
}

int Graph::get_id_by_name(std::string name)
{
    for (int i = 0; i < names.size(); i++)
        if (std::strcmp(names[i].c_str(), name.c_str()) == 0)
            return i;
    return -1;
}

std::string Graph::get_name_by_id(int id)
{
    if (id < 0 || id > names.size())
        return "";
    return names[id];
}

int Graph::get_commectedness() {
    return connectedness;
}