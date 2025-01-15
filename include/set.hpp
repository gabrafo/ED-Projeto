#pragma once

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

    int searchKey(const Trade& key) const;
}