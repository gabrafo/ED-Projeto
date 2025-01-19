# Projeto da disciplina Estruturas de Dados (GAC108)
## Descrição
Este projeto tem como objetivo a implementação de uma estrutura de dados baseada em listas chamada Sequence Set.

## O que é um Sequence Set?
Um Sequence Set é uma estrutura de dados que organiza grandes volumes de registros de maneira eficiente, utilizando arquivos binários divididos em conjuntos menores, chamados Sets. Cada Set contém uma sequência de registros ordenados e, a partir de cada Set, é possível acessar o próximo conjunto, garantindo que os dados estejam organizados e acessíveis de forma eficiente. Esta estrutura é útil para manipulação de grandes quantidades de dados de maneira que os dados sejam mantidos ordenados em sequência, facilitando buscas e inserções.

## Funcionalidades
O projeto tem como objetivo a implementação das seguintes funcionalidades:

- **Inserção de dados via arquivo texto**: Dados podem ser inseridos a partir de arquivos CSV.
- **Inserção de dados via entrada padrão**: Permitindo inserir registros manualmente.
- **Remoção de dados específicos**: Remover registros específicos da sequência.
- **Busca de dados específicos**: Localizar registros baseados em chave de pesquisa.

## Classes
O projeto utiliza as seguintes classes:

- `SequenceSet`: Representa o Sequence Set, com controle de cabeçalho (ID dos conjuntos e quantidade de elementos).
- `Set`: Representa um conjunto de registros, mantendo a ordem dos elementos dentro de cada conjunto. Cada Set possui um campo para o próximo conjunto (nextSetId), o que cria a cadeia de conjuntos.
- `Header`: Representa o cabeçalho do Sequence Set, com informações como quantidade de Sets, próximo ID de Set disponível e ID do primeiro Set.
- `Trade`: Estrutura que armazena os dados de cada registro, como ID, nome e outros campos relacionados.

## Como Compilar e Executar
Para compilar o projeto, será necessário ter um compilador C++ instalado em sua máquina.

Utilize o comando `g++` (ou similar) no terminal, passando os arquivos necessários:
```bash
g++ -Wall -Iinclude main.cpp src/header.cpp src/sequence_set.cpp src/set.cpp src/trade.cpp -omain
```

Para executar o programa: 
```bash
./main
```

## Notas de Desenvolvimento
Atualmente, estamos em processo de adição da funcionalidade de remover elementos.