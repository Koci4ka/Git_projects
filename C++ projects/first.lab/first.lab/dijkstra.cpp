#include "dijkstra.h"

std::list<Node> Dijkstra::find_path(Graph graph, Node start, Node goal)
{
	start.g = 0;
	start.parent = nullptr;
	insert_into_open(start);
	while (!open.empty())
	{
		Node current = get_min();
		pop_open();
		insert_into_closed(current);
		if (current.id == goal.id)
		{
			std::list<Node> path = reconstruct_path(current);
			write(graph);
			return path;
		}
		std::list<Node> neighbors = graph.get_neighbors(current);
		for (Node neighbor : neighbors)
		{
			if (in_closed(neighbor))
				continue;
			neighbor.g = current.g + graph.get_cost(neighbor.id, current.id);
			neighbor.parent = &closed.find(current.id)->second;
			insert_into_open(neighbor);
		}
	}
	return std::list<Node>();
}


void Dijkstra::insert_into_open(Node node) {
	std::list<Node>::iterator it = open.begin();
	for (auto element : open) {
		if (element.id == node.id) {
			if (element.g < node.g) {
				return;
			}
			open.erase(it);
			break;
		}
		it++;
	}
	it = open.begin();
	for (auto const& element : open) {
		if (node.g <= element.g) {
			open.insert(it, node);
			return;
		}
		it++;
	}
	open.push_back(node);
	return;
}

Node Dijkstra::get_min() {
	open.sort([](Node const& lhs, Node const& rhs)->bool {
		return lhs.g < rhs.g; });
	Node a;
	a = open.front();
	return a;
}


void Dijkstra::pop_open() {
	open.pop_front();
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


