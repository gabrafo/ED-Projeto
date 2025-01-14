# Árvore B+

É uma estrutura de dados, baseada na **Árvore B**, que é otimizada para operações em disco, utilizando, para isso, conceitos da estrutura baseada em listas ***Sequence Set***.

## Definição de Árvore B

Uma Árvore B é baseada na definição de Árvore B de ordem `m`, que satisfaz as seguintes propriedades:

- Cada nó pode ter no máximo `m` filhos.
- Cada nó (exceto a raiz e as folhas) deve ter, no mínimo, [`m`/2] filhos.
- Cada nó não-folha com `k` filhos, deve ter `k`-1 chaves.
- A raiz, se não for uma folha, deve ter pelo menos 2 filhos.
- Todos os nós folha estão no mesmo nível.

Esta definição formal é atribuída a Donald Knuth, em seu trabalho seminal The Art of Computer Programming, Volume 3: Sorting and Searching, na Seção 6.4, onde ele descreve a Árvore B e B*.

![Exemplo da estrutura de uma árvore B+.](./img/Exemplo%20de%20B+.png)

### Diferença entre Árvore B e Árvore B+

- Na **Árvore B**, os dados podem ser armazenados tanto nas folhas quanto nos nós intermediários.  
- Na **Árvore B+**, os dados são armazenados exclusivamente nas folhas, enquanto os nós intermediários servem apenas como índices.

## Operações na Árvore B+

As operações de **busca**, **inserção** e **remoção** na Árvore B+ envolvem algumas situações especiais, como a **inserção em página cheia**, a **divisão de nós** e a **fusão de nós**. Abaixo, explicamos essas operações e os casos que podem ocorrer durante seu processo.

### 1. Operação de Busca

A operação de **busca** na Árvore B+ é bastante eficiente devido ao uso dos índices nos nós intermediários. A busca ocorre até alcançar uma folha, onde a chave desejada é verificada. Como as folhas estão em um nível único e são conectadas em uma lista, a busca sequencial também é rápida.

#### Etapas:
1. **Início pela raiz**: Comece pela raiz da árvore.
2. **Busca nos nós intermediários**: Compare a chave de busca com os valores nos nós intermediários. Se a chave for menor que um índice, desça para o filho correspondente. Se não houver um índice menor, desça para o filho à direita.
3. **Chegada às folhas**: Continue até encontrar uma folha. No caso da Árvore B+, todos os dados estão nas folhas.
4. **Verificação na folha**: Após chegar à folha, verifique se a chave está presente. Se estiver, retorne o valor associado a ela. Caso contrário, retorne `null`, indicando que a chave não foi encontrada.

### 2. Operação de Inserção

A **inserção** na Árvore B+ segue um processo ordenado, mas pode envolver casos especiais, como **inserção em página cheia**, **divisão de nós** e **propagação de divisão até a raiz**.

#### Etapas:
1. **Busca pela posição de inserção**: A primeira etapa da inserção é localizar a folha em que a chave deve ser inserida. Isso é feito por meio da busca, que descende da raiz até uma folha.
   
2. **Inserção na folha**: Se a folha não estiver cheia, a chave é inserida na posição correta, mantendo a ordem crescente.

3. **Inserção em página cheia**:
   - Se a folha estiver cheia, a folha é dividida em duas.
   - O valor do meio da folha dividida é promovido para o nó pai, a fim de manter a propriedade de que os nós não podem ter mais do que o número máximo de chaves.
   
4. **Divisão de nó pai**:
   - Se o nó pai também estiver cheio após a promoção da chave, ele será dividido da mesma forma.
   - Isso pode se propagar até a raiz, que, se também estiver cheia, será dividida, podendo aumentar a altura da árvore.

#### Possíveis casos de inserção:
- **Inserção em folha não cheia**: A chave é simplesmente inserida no nó folha sem necessidade de divisão.
- **Inserção em folha cheia**: O nó folha é dividido, e a chave do meio é promovida para o nó pai.
- **Inserção que resulta em divisão até a raiz**: A divisão se propaga até a raiz, aumentando a altura da árvore.

### 3. Operação de Remoção

A **remoção** de uma chave de um nó folha pode resultar em um **nó subpreenchido**. Se isso ocorrer, é necessário realizar uma **redistribuição** de chaves ou uma **fusão de nós**, de modo a manter as propriedades da Árvore B+.

#### Etapas:
1. **Busca pela chave a ser removida**: Localize a chave na folha onde ela está armazenada.
   
2. **Remoção da chave**: Após encontrar a chave, ela é removida da folha.

3. **Redistribuição ou Fusão**:
   - **Redistribuição**: Se um nó irmão tiver mais chaves do que o necessário, uma chave será movida do nó irmão para o nó atual.
   - **Fusão**: Se a redistribuição não for possível, o nó atual é fundido com um irmão, e a chave do nó pai que apontava para o nó atual é removida.

#### Possíveis casos de remoção:
- **Remoção sem subpreenchimento**: Se a remoção não deixar o nó abaixo da quantidade mínima de chaves, o processo é simples e a árvore continua balanceada.
- **Remoção com subpreenchimento**: Quando a remoção deixa o nó abaixo da quantidade mínima de chaves, o nó precisa ser equilibrado, seja por **redistribuição** (movendo chaves de nós irmãos) ou por **fusão** (fundindo dois nós e removendo uma chave do nó pai).
- **Fusão até a raiz**: Caso a fusão propague até a raiz, a altura da árvore pode diminuir, caso a raiz perca um filho.