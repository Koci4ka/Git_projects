#include "astar.h"
#include <algorithm>

Result AStar::find_path(Graph graph, Node start, Node goal)
{
	int closed_count = 0;
	std::unordered_map<int, Node*> nodes;
	std::unordered_map<int, Node*>::const_iterator it;
	std::priority_queue< std::pair<int, Node*>, std::vector< std::pair<int, Node*> >, CustomCompare > open;
	Node* neighborPtr = new Node();
	neighborPtr->id = start.id;
	neighborPtr->i = start.i;
	neighborPtr->j = start.j;
	neighborPtr->f = start.f;
	neighborPtr->h = start.h;
	neighborPtr->g = 0;
	neighborPtr->parent = nullptr;
	neighborPtr->inOpened = true;
	open.push(std::make_pair(0, neighborPtr));
	nodes[start.id] = neighborPtr;
	while (!open.empty())
	{
		std::pair<int, Node*> current = open.top();
		open.pop();
		current.second->inOpened = false;
		if (!current.second->inClosed)
		{
			current.second->inClosed = true;
			closed_count++;
		}

		if (current.second->id == goal.id)
		{
			Result res = reconstruct_path(*nodes[goal.id]);
			res.expanded = closed_count;
			res.generated = nodes.size();
			res.cost = nodes[goal.id]->g;
			nodes.clear();
			return res;
		}

		if (current.first > current.second->f)
			continue;

		std::list<Node> neighbors = graph.get_neighbors(*(current.second));
		for (Node neighbor : neighbors)
		{
			it = nodes.find(neighbor.id);
			if (it == nodes.end())
			{
				neighborPtr = new Node();
				neighborPtr->id = neighbor.id;
				neighborPtr->i = neighbor.i;
				neighborPtr->j = neighbor.j;
				neighborPtr->f = neighbor.f;
				neighborPtr->h = neighbor.h;
			}
			else
			{
				neighborPtr = it->second;
			}

			if (neighborPtr->inClosed)
				continue;

			float coast = graph.get_cost(neighbor.id, current.second->id);
			if (neighborPtr->g > current.second->g + coast)
			{
				neighborPtr->g = current.second->g + coast;
				neighborPtr->h = h_value(*neighborPtr, goal, graph);
				neighborPtr->f = neighborPtr->g + neighborPtr->h;
				neighborPtr->parent = current.second;
				neighborPtr->inOpened = true;
				nodes[neighbor.id] = neighborPtr;
				open.push(std::make_pair(neighborPtr->f, neighborPtr)); //Использование приоритета f = g + h для очереди open
			}
		}
	}
	nodes.clear();
	Result res;
	res.expanded = closed_count;
	res.generated = nodes.size();
	res.cost = -1;
	res.path = std::list<Node>();
	return res;
}

Result AStar::reconstruct_path(Node goal) {
	Result res;
	res.path = std::list<Node>();
	Node current = goal;
	res.path.push_front(current);
	Node a;
	while (current.parent != 0) {
		a = *current.parent;
		res.path.push_front(a);
		current = a;
	}
	return res;
}


float AStar::h_value(Node current, Node goal, Graph graph) {
	float h = 0;
	if (graph.get_commectedness() == 4) {
		h = abs(current.i - goal.i) + abs(current.j - goal.j);
	}
	else if (graph.get_commectedness() == 8) {
		h = sqrt(2) * std::min(abs(current.i - goal.i), abs(current.j - goal.j)) + abs(abs(current.i - goal.i) - abs(current.j - goal.j));
	}
	return h;
}