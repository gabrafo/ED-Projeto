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


void SequenceSet::insert(Trade element)
{
    std::cout << "Iniciando inserção..." << std::endl;
    if (header.firstSetId == -1) {
        header.firstSetId = header.nextAvailableSetId;
        header.nextAvailableSetId++;
        Set newSet(header.firstSetId, 1, header.nextAvailableSetId);
        newSet.elements[0] = element;
        newSet.saveSetToFile();
        return; // Early-return
    }

    int currentSetId = header.firstSetId;
    bool inserted = false;

    while (currentSetId != -1 and !inserted) {
        Set currentSet;
        currentSet.loadSetFromFile();

        if(currentSet.isInRange(element)){ // Se o set atual está no intervalo de inserção do elemento...
            insertInSet(currentSet, element);
            inserted = true;
            return;
        }

        if (!inserted) {
            Set firstSet;
            firstSet.loadSetFromFileById(header.firstSetId);

            // Verifica se o elemento é maior que todos ou menor que todos
            if (element < firstSet.elements[0]) {
                insertInSet(firstSet, element);
                inserted = true;
            } else {
                // Se o elemento for maior que todos, insira no último conjunto
                int lastSetId = currentSetId-1;
                Set lastSet;
                lastSet.loadSetFromFileById(lastSetId);  // Usamos currentSetId, que é o último ID possível
                insertInSet(lastSet, element);
                inserted = true;
            }
        }
        
        currentSetId = currentSet.nextSetId;
    }
}

void SequenceSet::insertInSet(Set currentSet, Trade element) 
{
    if (currentSet.qntElements < SET_SIZE) {  // Se o conjunto não está cheio
        currentSet.insert(element); 
        currentSet.saveSetToFile();
        header.saveHeaderToFile();
    } else {
        // Se o conjunto está cheio, divide o conjunto
        splitSet(currentSet.setId, element);
    }
    std::cout << "Cabeçalho salvo!" << std::endl;
}

void SequenceSet::splitSet(int currentSetId, Trade element) 
{
    std::cout << "Dividindo o conjunto..." << std::endl;
    Set currentSet;
    currentSet.loadSetFromFileById(currentSetId);

    int mid = currentSet.qntElements / 2;

    int newSetId = header.nextAvailableSetId;
    Set newSet(newSetId, 0, -1);

    // Copiar metade superior dos elementos para o novo conjunto
    std::copy(currentSet.elements + mid, currentSet.elements + currentSet.qntElements, newSet.elements);
    newSet.qntElements = currentSet.qntElements - mid;

    // Atualizar o conjunto atual para conter apenas a metade inferior
    currentSet.qntElements = mid;

    // Inserir o elemento no conjunto correto
    if (element < newSet.elements[0]) {
        // Inserir no conjunto atual (metade inferior)
        std::cout << "Inserção na metade inferior..." << std::endl;
        currentSet.insert(element);
    } else {
        // Inserir no novo conjunto (metade superior)
        std::cout << "Inserção na metade superior..." << std::endl;
        newSet.insert(element);
    }

    // Atualizar o próximo ID do conjunto atual para apontar para o novo conjunto
    currentSet.nextSetId = newSetId;

    // Salvar ambos os conjuntos no disco
    currentSet.saveSetToFile();
    newSet.saveSetToFile();

    std::cout << "Conjuntos salvos!" << std::endl;

    header.qntSets++;
    header.updateNextAvailableSetId();

    std::cout << "Cabeçalho atualizado!" << std::endl;

    // Atualizar o header para salvar o próximo ID disponível
    header.saveHeaderToFile();
}