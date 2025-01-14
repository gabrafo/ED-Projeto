#include "BPlus.hpp"
#include <iostream>

BPlus::BPlus(int degree) : degree(degree), root(nullptr) {}

BPlus::~BPlus() {
    delete root;
}

BPlus::insertNonFull(Node* node, Trade key, Trade& promotedKey, Node*& splitNode) {
    // TODO()
}