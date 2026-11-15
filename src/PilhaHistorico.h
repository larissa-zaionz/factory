
#ifndef PILHA_HISTORICO_H
#define PILHA_HISTORICO_H

#include "Produto.h"

struct NoHistorico {
    Produto produto;
    NoHistorico* proximo;
};

// Adiciona um produto no topo do histórico.
void push(NoHistorico*& topo, Produto produto);

// Consulta o produto do topo.
bool peek(NoHistorico* topo, Produto& produto);

// Remove o produto do topo.
void pop(NoHistorico*& topo);

// Verifica se a pilha está vazia.
bool pilhaVazia(NoHistorico* topo);

// Libera toda a memória da pilha.
void liberarPilha(NoHistorico*& topo);

#endif
