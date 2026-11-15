
#include "PilhaHistorico.h"

// Adiciona um pedido ao topo da pilha.
// Parâmetros: topo (referência à pilha) e pedido.
// Retorno: nenhum.
void empilharHistorico(NoHistorico*& topo, Pedido pedido) {
    NoHistorico* novo = new NoHistorico;
    novo->pedido = pedido;
    novo->proximo = topo;
    topo = novo;
}

// Consulta o pedido do topo.
// Parâmetros: topo (início da pilha) e pedido (recebe o resultado).
// Retorno: true se encontrou, false se estiver vazia.
bool consultarTopoHistorico(NoHistorico* topo, Pedido& pedido) {
    if (topo == nullptr) {
        return false;
    }

    pedido = topo->pedido;
    return true;
}

// Remove o pedido do topo.
// Parâmetro: topo (referência à pilha).
// Retorno: nenhum.
void desempilharHistorico(NoHistorico*& topo) {
    if (topo == nullptr) {
        return;
    }

    NoHistorico* auxiliar = topo;
    topo = topo->proximo;
    delete auxiliar;
    auxiliar = nullptr;
}

// Verifica se a pilha está vazia.
// Parâmetro: topo (início da pilha).
// Retorno: true se vazia, false caso contrário.
bool pilhaVazia(NoHistorico* topo) {
    return topo == nullptr;
}

// Libera todos os nós da pilha.
// Parâmetro: topo (referência à pilha).
// Retorno: nenhum.
void liberarPilha(NoHistorico*& topo) {
    while (topo != nullptr) {
        desempilharHistorico(topo);
    }
}
