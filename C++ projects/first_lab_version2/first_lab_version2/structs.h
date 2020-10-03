#ifndef STRUCTS_H
#define STRUCTS_H
#include <list>

struct Node
{
Node(int _id = -1, Node* _parent = nullptr, int _i = -1, int _j = -1, bool _inOpened = false, bool _inClosed = false) :id(_id), parent(_parent), i(_i), j(_j), inOpened(_inOpened), inClosed(_inClosed) { g = INFINITY; }
int id;
float g;
float f;
float h;
Node* parent;
int i;
int j;
bool inOpened;
bool inClosed;

};

struct Result
{
float runtime;
float cost;
int expanded; // amount of expanded nodes, equal to the amount of nodes in closed list
int generated; // amount of totally generated nodes, equal to the sum of nodes in open and closed lists
std::list<Node> path;
};

#endif // STRUCTS_H