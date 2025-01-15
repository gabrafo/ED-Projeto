#pragma once

#include <fstream>

#include "header.hpp"
#include "set.hpp"
#include "trade.hpp"
#include "utils.hpp"

class SequenceSet
{
    private:
        Header header;
        void splitSet(int setId);

    public:
        void insert(Trade element);
        void splitSet(int currentSetId, Trade element);
        //void remove(Trade element);
        //Trade* search(Trade key);
}