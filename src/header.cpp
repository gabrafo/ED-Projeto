#include "header.hpp"
#include <iostream>

Header::Header()
{
    qntSets = 0;
    firstSetId = -1;
    nextAvailableSetId = 0;
}

void Header::serialize(std::ofstream& out) const
{
    out.write(reinterpret_cast<const char*>(&qntSets), sizeof(qntSets));
    out.write(reinterpret_cast<const char*>(&firstSetId), sizeof(firstSetId));
    out.write(reinterpret_cast<const char*>(&nextAvailableSetId), sizeof(nextAvailableSetId));
}

void Header::deserialize(std::ifstream& in)
{
    in.read(reinterpret_cast<char*>(&qntSets), sizeof(qntSets));
    in.read(reinterpret_cast<char*>(&firstSetId), sizeof(firstSetId));
    in.read(reinterpret_cast<char*>(&nextAvailableSetId), sizeof(nextAvailableSetId));
}

void Header::saveHeaderToFile() const
{
    std::ofstream out("bins/header.bin", std::ios::binary);
    if (out.is_open()) {
        serialize(out);
        out.close();
    } else {
        throw std::runtime_error("Unable to open file for writing.");
    }
}

void Header::loadHeaderFromFile()
{
    std::ifstream in("header.bin", std::ios::binary);
    if (in.is_open()) {
        deserialize(in);
        in.close();
    } else {
        throw std::runtime_error("Unable to open file for reading.");
    }
}

void Header::updateNextAvailableSetId() {
    int currentSetId = firstSetId;

    bool emptySetFound = false;

    while (currentSetId != -1 and !emptySetFound) {
        Set currentSet;
        currentSet.loadSetFromFileById(currentSetId);

        // Se encontrar um set vazio, use esse ID
        if (currentSet.qntElements == 0) {
            nextAvailableSetId = currentSetId;
            std::cout << "Conjunto vazio encontrado. Próximo ID disponível: " << nextAvailableSetId << std::endl;
            emptySetFound = true;
        }

        // Caso contrário, continue verificando o próximo set
        currentSetId = currentSet.nextSetId;
    }

    if(!emptySetFound){
        nextAvailableSetId = qntSets;
        std::cout << "Nenhum conjunto vazio encontrado. Próximo ID disponível: " << nextAvailableSetId << std::endl;
    }

    saveHeaderToFile();
}