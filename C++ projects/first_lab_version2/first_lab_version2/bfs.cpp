#include "bfs.h"

Result BFS::find_path(Graph graph, Node start, Node goal)
{
	int closed_count = 0;
	std::unordered_map<int, Node*> nodes;
	std::unordered_map<int, Node*>::const_iterator it;
	std::queue<Node*> open;
	Node* neighborPtr = new Node();
	neighborPtr->id = start.id;
	neighborPtr->i = start.i;
	neighborPtr->j = start.j;
	neighborPtr->g = 0;
	neighborPtr->parent = nullptr;
	neighborPtr->inOpened = true;
	open.push(neighborPtr);
	nodes[start.id] = neighborPtr;
	while (!open.empty())
	{
		Node* current = open.front();
		open.pop();
		current->inOpened = false;
		current->inClosed = true;
		closed_count++;
		std::list<Node> neighbors = graph.get_neighbors(*current);
		if (current->id == goal.id)
		{
			Result res = reconstruct_path(*nodes[goal.id]);
			res.expanded = closed_count;
			res.generated = nodes.size();
			res.cost = nodes[goal.id]->g;
			nodes.clear();
			return res;
		}
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
			if (neighborPtr->inOpened || neighborPtr->inClosed)
				continue;
			neighborPtr->inOpened = true;
			neighborPtr->g = current->g + 1;
			neighborPtr->parent = current;
			nodes[neighbor.id] = neighborPtr;
			open.push(neighborPtr);
		}
	}
	nodes.clear();
	Result res;
	res.expanded = closed_count;
	res.generated = nodes.size();
	res.cost = -1; //не найден путь 
	res.path = std::list<Node>();
	return res;
}


Result BFS::reconstruct_path(Node goal) {
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