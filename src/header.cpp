#include "header.hpp"

Header::Header()
{
    qntSets = 0;
    firstSet = nullptr;
    nextAvailableSet = nullptr;
}

Header::~Header()
{
    Set* aux = firstSet;
    Set* tmp;

    while (aux != nullptr)
    {
        tmp = aux;
        aux = aux->next;
        delete tmp;
    }
}