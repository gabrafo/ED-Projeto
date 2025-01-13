#include "node.hpp"

Node::Node(int degree, bool isLeaf)
    : numKeys(0), isLeaf(isLeaf), next(nullptr)
{
    keys = new Trade[degree - 1];
    if (!isLeaf) {
        children = new Node*[degree];
    } else {
        children = nullptr;
    }
}

Node::~Node()
{
    delete[] keys;
    if (children != nullptr) {
        delete[] children;
    }
}

int Node::searchKey(Trade key)
{
    for (int i = 0; i < numKeys; i++) {
        if (keys[i] == key) {
            return i;
        }
    }
    return -1;
}