#pragma once

#include <fstream>

#include "header.hpp"
#include "trade.hpp"
#include "utils.hpp"

struct Set
{
    int setId;
    Trade[SET_SIZE] elements;
    int qntElements;
    int nextISetId;

    Set();
    Set(int setId, int qntElements, int nextISetId);

    void insert(Trade& element)
    int searchKey(const Trade& key) const;
    bool isInRange(const Trade& item) const;
    void quicksort(Trade[SET_SIZE]& elements, int start, int end);
    int binarySearch(const Trade& item, int lastPos, bool insertion) const;
    int findInsertPosition(const Trade& key) const;
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
    void saveSetToFile() const;
    void loadSetFromFile();
    void loadSetFromFileById(int setId);
}