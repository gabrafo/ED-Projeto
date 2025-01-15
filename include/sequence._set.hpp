#pragma once

#include "header.hpp"
#include "set.hpp"

class SequenceSet
{
    private:
        Header header;

    public:
        void insert(Trade element);
        void remove(Trade element);
        Trade* search(Trade key);
}