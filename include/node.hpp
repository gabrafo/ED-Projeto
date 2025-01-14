#pragma once

#include <string>
#include "trade.hpp"

struct Node
{
    int numKeys;        
    bool isLeaf;        
    Trade* keys;        
    Node** children; // Vetor dinâmico de objetos "Node", por isso o asterisco duplo
    Node* next;    

    Node(int degree, bool isLeaf);
    ~Node();

    int searchKey(Trade key);
}