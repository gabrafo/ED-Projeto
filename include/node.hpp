#pragma once

#include <string>
#include "trade.hpp"

class Node
{
    private:
        int numKeys;
        bool isLeaf;
        Trade* keys;
        Node** children; // Vetor dinâmico de objetos "Node", por isso o asterisco duplo
        Node* next;

        Node(int degree, bool isLeaf);
        ~Node();

    public:
        int searchKey(Trade key);
}