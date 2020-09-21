#ifndef STRUCTS_H
#define STRUCTS_H

struct Node
{
    Node(int _id = -1, Node* _parent = nullptr, int _i = -1, int _j = -1) :id(_id), parent(_parent), i(_i), j(_j) { g = 0; }
    int id;
    float g;
    float f;
    float h;
    Node* parent;
    int i;
    int j;

};

#endif // STRUCTS_H
