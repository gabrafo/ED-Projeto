#pragma once

#include "set.hpp"

struct Header
{
    int qntSets;
    int firstSetId;
    int nextAvailableSetId;

    Header();
    ~Header();
}