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
        Header getHeader() const;

        void insert(Trade element);
        void splitSet(int currentSetId, Trade element);
        Trade search(const Trade& searchKey) const;
        void remove(Trade element);
        void debugPrintAllElementsFromPackage(int setId) const;
};