
#ifndef PILHA_HISTORICO_H
#define PILHA_HISTORICO_H

#include "Produto.h"

struct NoHistorico {
    Pedido pedido;
    NoHistorico* proximo;
};

// Adiciona um pedido ao topo do histórico.
void empilharHistorico(NoHistorico*& topo, Pedido pedido);

// Consulta o pedido que está no topo.
bool consultarTopoHistorico(NoHistorico* topo, Pedido& pedido);

// Remove o pedido do topo.
void desempilharHistorico(NoHistorico*& topo);

// Verifica se a pilha está vazia.
bool pilhaVazia(NoHistorico* topo);

// Libera toda a memória da pilha.
void liberarPilha(NoHistorico*& topo);

#endif
