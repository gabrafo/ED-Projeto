#include "set.hpp"
#include <iostream>

Set::Set() : setId(0), elements(), qntElements(0), nextSetId(0) {}

Set::Set(int setId, int qntElements, int nextSetId)
    : setId(setId), elements(), qntElements(qntElements), nextSetId(nextSetId) {}

void Set::insert(Trade& element){
    int pos = findInsertPosition(element);

    std::copy_backward(elements + pos,
                    elements + qntElements,
                    elements + qntElements + 1);
    elements[pos] = element;
    qntElements++;
    saveSetToFile();
}

void Set::deleteElement(int pos){
    std::copy(elements + pos + 1,
              elements + qntElements,
              elements + pos);
    qntElements--;

    // Verifique se o conjunto atual tem menos que a metade de sua capacidade
    if(qntElements/2 < SET_SIZE/2){

        // Verificar se o próximo conjunto existe
        if(nextSetId != -1){
            Set nextSet;
            nextSet.loadSetFromFileById(nextSetId);

            // Caso o próximo conjunto tenha mais do que 50% de ocupação, empreste um elemento
            if(nextSet.qntElements > SET_SIZE/2){
                elements[qntElements] = nextSet.elements[0];
                nextSet.deleteElement(0);
                nextSet.saveSetToFile();
                qntElements++;
                saveSetToFile();
                return;
            }

            // Caso o próximo conjunto tenha menos que 50% de ocupação
            // e seja possível juntar os conjuntos, faça a união
            if(nextSet.qntElements + qntElements <= SET_SIZE){
                // Junta os conjuntos
                std::copy(nextSet.elements,
                          nextSet.elements + nextSet.qntElements,
                          elements + qntElements);
                qntElements += nextSet.qntElements;
                nextSetId = nextSet.nextSetId;
                nextSet.saveSetToFile();
                saveSetToFile();
                return;
            }
        }

    }

    saveSetToFile();
}

bool Set::isInRange(const Trade& item) const {
    return (item >= elements[0] and item <= elements[qntElements - 1]);
}

int Set::binarySearch(const Trade& item, int lastPos, bool insertion) const
{
    int low = 0;
    int high = lastPos;
    
    while(low <= high){
        int mid = (low + high)/2;
        Trade guess = elements[mid];
        
        if(guess == item){
            return mid; // Elemento já existe
        }

        if (guess > item){
            high = mid - 1; // Está na parte direita
        }

        if(guess < item){
            low = mid + 1; // Está na parte esquerda
        }

    }
    
    return insertion ? low : -1; // Retorna a posição para inserção ou -1 (caso apenas queira encontrar o elemento)
}

int Set::findInsertPosition(const Trade& key) const
{
    std::cout << "Procurando posição para inserir elemento..." << std::endl;
    return binarySearch(key, qntElements - 1, true);
}

int Set::searchKey(const Trade& key) const
{
    return binarySearch(key, qntElements - 1, false);
}

void Set::serialize(std::ofstream& out) const 
{
    if (qntElements > SET_SIZE) {
        std::cerr << "Erro: número de elementos excede o limite permitido!" << std::endl;
        return;
    }
    out.write(reinterpret_cast<const char*>(&setId), sizeof(setId));
    out.write(reinterpret_cast<const char*>(&nextSetId), sizeof(nextSetId));
    out.write(reinterpret_cast<const char*>(&qntElements), sizeof(qntElements));
    for (int i = 0; i < qntElements; ++i) {
        elements[i].serialize(out);
    }
}

void Set::deserialize(std::ifstream& in)
{
    in.read(reinterpret_cast<char*>(&setId), sizeof(setId));
    in.read(reinterpret_cast<char*>(&nextSetId), sizeof(nextSetId));
    in.read(reinterpret_cast<char*>(&qntElements), sizeof(qntElements));

    if (qntElements > SET_SIZE) {
        std::cerr << "Erro: número de elementos excede o limite permitido!" << std::endl;
        return;
    }

    for (int i = 0; i < qntElements; ++i) {
        elements[i].deserialize(in);
    }
}

void Set::saveSetToFile() const
{
    std::string filename = "bins/package_" + std::to_string(setId) + ".bin";
    std::ofstream out(filename, std::ios::binary);
    serialize(out);
    std::cout << "Salvando conjunto com ID: " << std::to_string(setId) << std::endl;
    std::cout << "package_" << std::to_string(setId) << ".bin" << std::endl;
    std::cout << "Quantidade de elementos: " << std::to_string(qntElements) << std::endl;
    std::cout << "Menor countryCode: " << elements[0].getCountryCode() << std::endl;
    std::cout << "Maior countryCode: " << elements[qntElements-1].getCountryCode() << std::endl;
    std::cout << "Próximo arquivo: " << std::to_string(nextSetId) << std::endl;
    std::cout << "Conjunto salvo no arquivo!" << std::endl;
}

void Set::loadSetFromFileById(int setId)
{
    std::string filename = "bins/package_" + std::to_string(setId) + ".bin";
    std::ifstream in(filename, std::ios::binary);
    deserialize(in);
}

bool Set::isFull() const
{
    return qntElements == SET_SIZE;
}