#include "sequence_set.hpp"

#include <iostream>

Header SequenceSet::getHeader() const
{
    return header;
}

Trade SequenceSet::search(const Trade& searchKey) const 
{
    int currentSetId = header.firstSetId;

    while (currentSetId != -1) {
        Set currentSet;
        currentSet.loadSetFromFileById(currentSetId);  // Carregar o Set pelo ID atual

        // Verifica se o Set está no intervalo certo para o searchKey
        if (currentSet.isInRange(searchKey)) {
            // Usamos binarySearch para procurar o Trade dentro do Set
            int foundIndex = currentSet.searchKey(searchKey);
            if (foundIndex != -1) {
                // Encontramos o Trade no Set
                return currentSet.elements[foundIndex];
            }
        }

        // Se não encontrou, passa para o próximo Set
        currentSetId = currentSet.nextSetId;
    }

    // Caso o trade não seja encontrado após percorrer todos os sets
    throw std::runtime_error("Trade não encontrado.");
}

void SequenceSet::remove(Trade element){
    int currentSetId = header.firstSetId;
     while (currentSetId != -1) {
        Set currentSet;
        currentSet.loadSetFromFileById(currentSetId);

        if (currentSet.isInRange(element)) {
            // Usamos binarySearch para procurar o Trade dentro do Set
            int foundIndex = currentSet.searchKey(element);
            if (foundIndex != -1) {
                currentSet.deleteElement(foundIndex);
                return;
            }
        }

        // Se não encontrou, passa para o próximo Set
        currentSetId = currentSet.nextSetId;
    }
}

void SequenceSet::insert(Trade element)
{
    std::cout << "Iniciando inserção..." << std::endl;

    if(header.qntSets == 0) {
        Set newSet;
        // Caso especial: nenhum conjunto ainda existe
        std::cout << "Primeiro elemento sendo inserido..." << std::endl;
        header.firstSetId = header.nextAvailableSetId;
        header.qntSets++;

        newSet = Set(header.firstSetId, 0, -1);
        newSet.elements[0] = element;
        newSet.qntElements++;

        header.nextAvailableSetId++;
        newSet.saveSetToFile();
        header.saveHeaderToFile();
        return;
    }

    int currentSetId = header.firstSetId;
    Set currentSet;
    bool inserted = false;

    while (currentSetId != -1 and !inserted) {
        currentSet.loadSetFromFileById(currentSetId);

        // Caso 1: O elemento está no intervalo do conjunto atual
        if(currentSet.isInRange(element)){
            std::cout << "Elemento está no intervalo do set atual!" << std::endl;

            if(!currentSet.isFull()){
                std::cout << "Inserindo em set com espaço disponível..." << std::endl;
                currentSet.insert(element);
            } else {
                std::cout << "Set atual está cheio!" << std::endl;
                splitSet(currentSetId, element);
            }
            inserted = true;
        } else if (currentSet.nextSetId != -1) { // Caso 2: Verificar relação com o próximo conjunto
            // Set atual não está no intervalo do elemento e não é o último set
            Set nextSet;
            nextSet.loadSetFromFileById(currentSet.nextSetId);

            if (element < nextSet.elements[0]) {
                std::cout << "Elemento pertence entre os conjuntos ID " 
                          << currentSet.setId << " e ID " << nextSet.setId << "." << std::endl;

                // Inserir no conjunto atual se houver espaço
                if (!currentSet.isFull()) {
                    currentSet.insert(element);
                    inserted = true;
                } else {
                    std::cout << "Conjunto ID " << currentSet.setId 
                              << " está cheio. Realizando divisão." << std::endl;
                    splitSet(currentSetId, element);
                    inserted = true;
                }
            }
        } else {
            std::cout << "Elemento pertence ao último conjunto." << std::endl;
            if (!currentSet.isFull()) {
                std::cout << "Inserindo no último conjunto..." << std::endl;
                currentSet.insert(element);
                inserted = true;
            } else {
                std::cout << "Último conjunto está cheio. Realizando divisão." << std::endl;
                splitSet(currentSetId, element);
                inserted = true;
            }
        }

        currentSetId = currentSet.nextSetId;
    }

    if(inserted){
        return;
    }

    currentSetId = currentSet.setId;

    std::cout << "Inserindo em novo set..." << std::endl;

    Set newSet(header.nextAvailableSetId, 0, -1);
    newSet.elements[0] = element;
    newSet.qntElements++;
    
    newSet.saveSetToFile();

    Set lastSet;
    lastSet.loadSetFromFileById(currentSetId);
    lastSet.nextSetId = newSet.setId;

    header.qntSets++;
    header.updateNextAvailableSetId();
    lastSet.saveSetToFile();
}

void SequenceSet::splitSet(int currentSetId, Trade element) 
{
    std::cout << "Dividindo o conjunto..." << std::endl;
    Set currentSet;
    currentSet.loadSetFromFileById(currentSetId);

    int mid = currentSet.qntElements / 2;

    int newSetId = header.nextAvailableSetId;
    Set newSet(newSetId, 0, currentSet.nextSetId);

    // Copiar metade superior dos elementos para o novo conjunto
    std::copy(currentSet.elements + mid, currentSet.elements + currentSet.qntElements, newSet.elements);
    newSet.qntElements = currentSet.qntElements - mid;

    // Atualizar o conjunto atual para conter apenas a metade inferior
    currentSet.qntElements = mid;

    // Inserir o elemento no conjunto correto
    if (element < newSet.elements[0]) {
        std::cout << "Elemento pertence à metade inferior. Inserindo no conjunto atual..." << std::endl;
        currentSet.insert(element);
    } else {
        std::cout << "Elemento pertence à metade superior. Inserindo no novo conjunto..." << std::endl;
        newSet.insert(element);
    }

    // Atualizar o próximo ID do conjunto atual para apontar para o novo conjunto
    currentSet.nextSetId = newSetId;

    // Salvar ambos os conjuntos no disco
    currentSet.saveSetToFile();
    newSet.saveSetToFile();

    header.qntSets++;

    header.updateNextAvailableSetId();
}

void SequenceSet::debugPrintAllElementsFromPackage(int setId) const {
    Set currentSet;
    currentSet.loadSetFromFileById(setId);

    std::cout << "Conjunto ID: " << currentSet.setId << std::endl;
    std::cout << "Quantidade de elementos: " << currentSet.qntElements << std::endl;

    // Exibe todos os elementos do conjunto atual
    std::cout << "Elementos do conjunto " << currentSet.setId << ": ";
    for (int i = 0; i < currentSet.qntElements; ++i) {
        std::cout << currentSet.elements[i].toString() << std::endl;
    }
    std::cout << std::endl;

    // Se houver um próximo conjunto, exibe o ID do próximo conjunto
    if (currentSet.nextSetId != -1) {
        std::cout << "Próximo conjunto ID: " << currentSet.nextSetId << std::endl;
    } else {
        std::cout << "Este é o último conjunto." << std::endl;
    }
}

void SequenceSet::debugPrintAllElements() const {
    std::cout << "--- Início da depuração ---" << std::endl;
    int currentSetId = header.firstSetId;

    // Percorre todos os conjuntos enquanto houver um conjunto válido
    while (currentSetId != -1) {
        Set currentSet;
        currentSet.loadSetFromFileById(currentSetId);  // Carregar o conjunto atual

        std::cout << "Conjunto ID: " << currentSetId << std::endl;
        std::cout << "Quantidade de elementos: " << currentSet.qntElements << std::endl;

        // Exibe todos os elementos do conjunto atual
        std::cout << "Elementos do conjunto " << currentSetId << ": ";
        for (int i = 0; i < currentSet.qntElements; ++i) {
            std::cout << currentSet.elements[i].getCountryCode() << " ";
        }
        std::cout << std::endl;

        // Se houver um próximo conjunto, exibe o ID do próximo conjunto
        if (currentSet.nextSetId != -1) {
            std::cout << "Próximo conjunto ID: " << currentSet.nextSetId << std::endl;
        } else {
            std::cout << "Este é o último conjunto." << std::endl;
        }

        // Passa para o próximo conjunto
        currentSetId = currentSet.nextSetId;
    }

    std::cout << "--- Fim da depuração ---" << std::endl;
}
