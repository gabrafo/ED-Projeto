#pragma once

#include "set.hpp"

struct Header
{
    int qntSets;
    Set* firstSet;
    Set* nextAvailableSet;
}