#include "set.hpp"

Set(){}

Set(int setId, int qntElements, int nextISetId) 
: setId(setId), qntElements(qntElements), nextISetId(nextISetId){}

void Set::insert(Trade& element){
    int pos = findInsertPosition(element);

    std::copy_backward(elements + pos,
                    elements + qntElements,
                    elements + qntElements + 1);
    elements[pos] = element;
    qntElements++;
}

bool Set::isInRange(const Trade& item) const {
    if (qntElements == 0) return true; // Conjunto vazio, aceita qualquer elemento.
    return (item >= elements[0] && item <= elements[qntElements - 1]);
}

// Usa o elemento mediano como pivô.
void Set::quicksort(Trade[SET_SIZE]& elements, int start, int end) 
{
    if (start >= end) return; // Caso-base: percorreu todos os elementos do vetor.

    // Caso recursivo: ainda há elementos a serem ordenados.
    int pivo = elements[(start + end) / 2];
    int i = start, j = end;

    // Particionamento in-place
    while (i <= j) {
        while (elements[i] < pivo) i++;
        while (elements[j] > pivo) j--;
        if (i <= j) {
            swap(elements[i], elements[j]);
            i++;
            j--;
        }
    }

    quicksort(elements, start, j);
    quicksort(elements, i, end);
}

int Set::binarySearch(const Trade& item, int lastPos, bool insertion) const
{
    int low = 0;
    int high = lastPos;
    
    while(low <= high){
        int mid = (low + high)/2;
        Trade guess = elements[mid];

        if (guess == item){
            return mid; // Acertou!
        }

        if (guess > item){
            high = mid - 1; // Está na parte direita
        }

        if(guess < item){
            low = mid + 1; // Está na parte esquerda
        }
    }

    return allowInsert ? low : -1; // Retorna a posição para inserção ou -1 (caso apenas queira encontrar o elemento)
}

int Set::findInsertPosition(const Trade& key) const
{
    return binarySearch(key, qntElements - 1, true);
}

int Set::searchKey(const Trade& key) const
{
    return binarySearch(key, qntElements - 1, false);
}

void Set::serialize(std::ofstream& out) const 
{
    out.write(reinterpret_cast<const char*>(&setId), sizeof(setId));
    out.write(reinterpret_cast<const char*>(&nextSetId), sizeof(nextSetId));
    out.write(reinterpret_cast<const char*>(&qntElements), sizeof(qntElements));
    for (int i = 0; i < qntElements; ++i) {
        trades[i].serialize(out);
    }
}

void Set::deserialize(std::ifstream& in)
{
    in.read(reinterpret_cast<char*>(&setId), sizeof(setId));
    in.read(reinterpret_cast<char*>(&nextSetId), sizeof(nextSetId));
    in.read(reinterpret_cast<char*>(&qntElements), sizeof(qntElements));
    for (int i = 0; i < qntElements; ++i) {
        trades[i].deserialize(in);
    }
}

void Set::saveSetToFile() const
{
    std::string filename = "package_" + std::to_string(setId) + ".bin";
    std::ofstream out(filename, std::ios::binary);
    serialize(out);
}

void Set::loadSetFromFile()
{
    std::string filename = "package_" + std::to_string(setId) + ".bin";
    std::ifstream in(filename, std::ios::binary);
    deserialize(in);
}

void Set::loadSetFromFileById(int setId)
{
    std::string filename = "package_" + std::to_string(setId) + ".bin";
    std::ifstream in(filename, std::ios::binary);
    deserialize(in);
}