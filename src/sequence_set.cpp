#include "sequence_set.hpp"

void SequenceSet::insert(Trade element)
{
    if (header.firstSetId == -1) {
        header.firstSetId = header.nextAvailableSetId;
        header.nextAvailableSetId++;
        Set newSet(header.firstSetId, 1, header.nextAvailableSetId);
        newSet.elements[0] = element;
        newSet.saveSetToFile();
        return; // Early-return
    }

    int currentSetId = header.firstSetId;
    while (currentSetId != -1) {
        Set currentSet;
        currentSet.loadSetFromFile();

        if(currentSet.isInRange(element)){ // Se o set atual está no intervalo de inserção do elemento...
            if(currentSet.qntElements < SET_SIZE) { // Se o set atual não está cheio
                currentSet.insert(element);
                currentSet.saveSetToFile();
                return; // Early-return
            }

            // Se o set atual está cheio, precisamos dividir o set atual
            splitSet(currentSetId, element);
            return;
        }
        
        currentSetId = currentSet.nextSetId;
    }
}

void SequenceSet::splitSet(int currentSetId, Trade element) {
    Set currentSet = loadSetFromFile(currentSetId);

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
        // Inserir no conjunto atual (metade inferior)
        insertInSet(element, currentSet);
    } else {
        // Inserir no novo conjunto (metade superior)
        newSet.insert(element);
    }

    // Atualizar o próximo ID do conjunto atual para apontar para o novo conjunto
    currentSet.nextSetId = newSetId;

    // Salvar ambos os conjuntos no disco
    currentSet.saveSetToFile();
    newSet.saveSetToFile();

    header.updateNextAvailableSetId();

    // Atualizar o header para salvar o próximo ID disponível
    header.saveHeaderToFile();
}