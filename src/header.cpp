#include "header.hpp"

Header::Header()
{
    qntSets = 0;
    firstSetId = -1;
    nextAvailableSetId = 0;
}

void serialize(std::ofstream& out) const
{
    out.write(reinterpret_cast<const char*>(&qntSets), sizeof(qntSets));
    out.write(reinterpret_cast<const char*>(&firstSetId), sizeof(firstSetId));
    out.write(reinterpret_cast<const char*>(&nextAvailableSetId), sizeof(nextAvailableSetId));
}

void deserialize(std::ifstream& in)
{
    in.read(reinterpret_cast<char*>(&qntSets), sizeof(qntSets));
    in.read(reinterpret_cast<char*>(&firstSetId), sizeof(firstSetId));
    in.read(reinterpret_cast<char*>(&nextAvailableSetId), sizeof(nextAvailableSetId));
}

void Header::saveHeaderToFile() const
{
    std::ofstream out("header.bin", std::ios::binary);
    if (out.is_open()) {
        serialize(out);
        out.close();
    } else {
        throw std::runtime_error("Unable to open file for writing: " + filename);
    }
}

void Header::loadHeaderFromFile()
{
    std::ifstream in("header.bin", std::ios::binary);
    if (in.is_open()) {
        deserialize(in);
        in.close();
    } else {
        throw std::runtime_error("Unable to open file for reading: " + filename);
    }
}

void Header::updateNextAvailableSetId() {
    int currentSetId = firstSetId;

    bool foundEmptySet = false;
    while (currentSetId != -1 and !foundEmptySet) {
        Set currentSet;
        currentSet.loadSetFromFile(currentSetId);

        // Se encontrar um set vazio, use esse ID
        if (currentSet.qntElements == 0) {
            nextAvailableSetId = currentSetId;
            foundEmptySet = true;
        }

        // Caso contrário, continue verificando o próximo set
        currentSetId = currentSet.nextSetId;
    }

    // Se não encontrar nenhum set vazio, incrementa o nextAvailableSetId
    if (!foundEmptySet) {
        header.nextAvailableSetId = header.qntSets + 1;
    }
}