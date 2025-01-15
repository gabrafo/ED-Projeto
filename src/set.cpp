#include "set.hpp"

Set(){}

Set(int setId, int qntElements, int nextISetId) 
: setId(setId), qntElements(qntElements), nextISetId(nextISetId){}


int Set::binarySearch(const Trade& item, int lastPos) const
{
    int low = 0;
    int high = lastPos;
    
    while(low <= high){
        int middle = (low + high)/2;
        Trade guess = elements[middle];

        if (guess == item){
            return middle; // Acertou!
        }

        if (guess > item){
            high = middle - 1; // Está na parte direita
        }

        if(guess < item){
            low = middle + 1; // Está na parte esquerda
        }
    }

    return -1;
}

int Set::searchKey(const Trade& key) const
{
    return binarySearch(key, qntElements);
}