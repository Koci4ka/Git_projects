#include "dijkstra.h"

std::list<Node> Dijkstra::find_path(Graph graph, Node start, Node goal)
{
	std::priority_queue< std::pair<int, Node>, std::vector< std::pair<int, Node> >, CustomCompare > open;
	start.g = 0;
	start.parent = nullptr;
	open.push(std::make_pair(0, start));
	while (!open.empty())
	{
		std::pair<int, Node> current = open.top();
		open.pop();
		if (current.first > current.second.g)
			continue;
		std::list<Node> neighbors = graph.get_neighbors(current.second);
		for (Node neighbor : neighbors)
		{
			if (neighbor.g > current.second.g + graph.get_cost(neighbor.id, current.second.id)) {
				neighbor.g = current.second.g + graph.get_cost(neighbor.id, current.second.id);
				neighbor.parent = &current.second;
				open.push(std::make_pair(neighbor.g, neighbor));
			}
		}
	}
	if (goal.visited)
	{
		std::list<Node> path = reconstruct_path(goal);
		write(graph);
		return path;
	}
	return std::list<Node>();
}


std::list<Node> Dijkstra::reconstruct_path(Node goal) {
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

void Dijkstra::write(Graph graph) {
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


