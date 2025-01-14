#pragma once

#include "node.hpp"
#include "trade.hpp"

class BPlus
{
    private:
        // Ordem da árvore
        int degree;
        void insertNonFull(Node* node, Trade key, Trade& promotedKey, Node*& splitNode);
        void splitChild(Node* parent, int index, Node* child, Trade& promotedKey, Node*& splitNode);

    public:
        Node* root;

        // Uso de "explicit" para evitar conversões indesejadas
        explicit BPlus(int degree);
        ~BPlus();

        void insert(Trade key);
        void print() const;
        Node* search(Trade key) const;
}