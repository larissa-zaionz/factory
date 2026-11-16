
#include "PilhaHistorico.h"

// Adiciona um produto no topo do histórico.
void push(NoHistorico*& topo, Produto produto) {
    NoHistorico* novo = new NoHistorico;
    novo->produto = produto;
    novo->proximo = topo;
    topo = novo;
}

// Consulta o produto do topo.
bool peek(NoHistorico* topo, Produto& produto) {
    if (topo == nullptr) {
        return false;
    }

    produto = topo->produto;
    return true;
}

// Remove o produto do topo.
void pop(NoHistorico*& topo) {
    if (topo == nullptr) {
        return;
    }

    NoHistorico* auxiliar = topo;
    topo = topo->proximo;
    delete auxiliar;
    auxiliar = nullptr;
}

// Verifica se a pilha está vazia.
bool pilhaVazia(NoHistorico* topo) {
    return topo == nullptr;
}

// Libera toda a memória da pilha.
void liberarPilha(NoHistorico*& topo) {
    while (topo != nullptr) {
        pop(topo);
    }
}
