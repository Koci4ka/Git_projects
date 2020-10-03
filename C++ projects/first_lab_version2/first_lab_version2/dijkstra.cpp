#include "dijkstra.h"

Result Dijkstra::find_path(Graph graph, Node start, Node goal)
{
	int closed_count = 0;
	std::unordered_map<int, Node*> nodes;
	std::unordered_map<int, Node*>::const_iterator it;
	std::priority_queue< std::pair<float, Node*>, std::vector< std::pair<float, Node*> >, CustomCompare > open;
	Node* neighborPtr = new Node();
	neighborPtr->id = start.id;
	neighborPtr->i = start.i;
	neighborPtr->j = start.j;
	neighborPtr->g = 0;
	neighborPtr->parent = nullptr;
	neighborPtr->inOpened = true;
	open.push(std::make_pair(0.0, neighborPtr));
	nodes[start.id] = neighborPtr;

	while (!open.empty())
	{
		std::pair<float, Node*> current = open.top();
		open.pop();
		current.second->inOpened = false;
		if (!current.second->inClosed)
		{
			current.second->inClosed = true;
			closed_count++;
		}

		if (current.first > current.second->g)
			continue;

		if (current.second->id == goal.id)
		{
			Result res = reconstruct_path(*nodes[goal.id]);
			res.expanded = closed_count;
			res.generated = nodes.size();
			res.cost = nodes[goal.id]->g;
			nodes.clear();
			return res;
		}
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
				neighborPtr->parent = current.second;
				neighborPtr->inOpened = true;
				nodes[neighbor.id] = neighborPtr;
				open.push(std::make_pair(neighborPtr->g, neighborPtr));
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


Result Dijkstra::reconstruct_path(Node goal) {
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