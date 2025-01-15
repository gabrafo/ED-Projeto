#pragma once

#include <stdexcept>
#include <fstream>

#include "set.hpp"

struct Header
{
    int qntSets;
    int firstSetId;
    int nextAvailableSetId;

    Header();  // Construtor padrão
    ~Header(); // Destruidor (não necessário, mas bom incluir)

    // Métodos de serialização
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);

    // Métodos para salvar e carregar o header no arquivo
    void saveHeaderToFile() const;
    void loadHeaderFromFile();

    // Atualizar o próximo ID disponível para sets
    void updateNextAvailableSetId();
};