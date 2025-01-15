#include "header.hpp"
#include "set.hpp"
#include "trade.hpp"
#include "utils.hpp"

void SequenceSet::insert(Trade element)
{
    if (header.firstSetId == -1) {
        header.firstSetId = header.nextAvailableSetId;
        header.nextAvailableSetId++;
        Set newSet(header.firstSetId, 1, header.nextAvailableSetId);
        newSet.elements[0] = element;
        return; // Early-return
    }

    // TODO: Implementar caso de inserção em Sequence Set não vazio.
    // Precisamos acessar os sets da memória com operações de In/Out usando serialização e desserialização de dados do arquivo binário.
}