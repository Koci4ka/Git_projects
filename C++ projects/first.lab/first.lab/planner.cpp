#include "planner.h"

std::list<Node> Planner::find_path(Graph graph, Node start, Node goal)
{
    std::cout << "Looking for path\n";
    return std::list<Node>();
}

std::list<Node> Planner::reconstruct_path(Node node)
{
    std::cout << "Reconstructing path\n";
    return std::list<Node>();
}

Node Planner::get_min()
{
    std::cout << "Getting Node with min g-value from OPEN\n";
    return Node();
}

void Planner::pop_open()
{
    std::cout << "Erasing first element from OPEN\n";
    return;
}

bool Planner::in_open(Node node)
{
    std::cout << "Checking node in OPEN\n";
    for (auto i : open) {
        if (i.id == node.id) {
            return true;
        }
    }
    return false;
}

bool Planner::in_closed(Node node)
{
    std::cout << "Checking node in CLOSED\n";
    for (auto i : closed) {
        if (i.first == node.id) {
            return true;
        }
    }
    return false;
}

void Planner::insert_into_open(Node node)
{
    std::cout << "Inserting node into OPEN\n";
    return;
}

void Planner::insert_into_closed(Node node)
{
    closed[node.id] = node;
    std::cout << "Inserting node into CLOSED\n";
    return;
}
