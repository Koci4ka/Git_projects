#include "bfs.h"

std::list<Node> BFS::find_path(Graph graph, Node start, Node goal)
{
    start.g = 0;
    start.parent = nullptr;
    insert_into_open(start);
    while (!open.empty())
    {
        Node current = get_min();
        pop_open();
        insert_into_closed(current);
        std::list<Node> neighbors = graph.get_neighbors(current);
        if (current.id == goal.id)
        {
            std::list<Node> path = reconstruct_path(current);
            write(graph);
            return path;
        }
        for (Node neighbor : neighbors)
        {
            if (in_closed(neighbor) || in_open(neighbor))
                continue;
            neighbor.g = current.g + 1;
            neighbor.parent = &closed.find(current.id)->second;
            insert_into_open(neighbor);

        }
    }
    return std::list<Node>();
}

void BFS::insert_into_open(Node node) {
    open.push_back(node);
}

void BFS::pop_open() {
    open.pop_front();
}

Node BFS::get_min() {
    return open.front();
}


std::list<Node> BFS::reconstruct_path(Node goal) {
    std::list<Node> backpath;
    Node current = goal;
    backpath.push_front(current);
    Node a;
    while (current.parent != 0) {
        a = *current.parent;
        backpath.push_front(a);
        current = a;
    }
    return backpath;
}

void BFS::write(Graph graph) {
    if (graph.get_commectedness() == 4 || graph.get_commectedness() == 8) {
        std::cout << "\nOPENED n-m:";
        for (auto n : open) {
            std::cout << " " << n.id / 10 << "-" << n.id % 10 << " ";
        }

        std::cout << "\n" << "\nCLOSED n-m:";
        for (auto n : closed) {
            std::cout << " " << n.first / 10 << "-" << n.first % 10 << " ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "\nOPENED:";
        for (auto n : open) {
            std::cout << " " << graph.get_name_by_id(n.id) << " ";
        }

        std::cout << "\n" << "\nCLOSED:";
        for (auto n : closed) {
            std::cout << " " << graph.get_name_by_id(n.first) << " ";
        }
        std::cout << "\n";
    }
}