#pragma once

#include "header.hpp"
#include "trade.hpp"

const int SET_SIZE = 5000; // Definindo arbitrariamente a quantidade de elementos

struct Set
{
    Trade[SET_SIZE] elements;
    int qntElements;
    Set* next;

    int searchKey(Trade key);
}