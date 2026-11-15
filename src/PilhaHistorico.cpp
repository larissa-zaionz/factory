
#include "PilhaHistorico.h"

// Adiciona um produto no topo da pilha.
// Parâmetros: topo (referência ao início da pilha) e produto.
// Retorno: nenhum.
void empilharHistorico(NoHistorico*& topo, Produto produto) {
    NoHistorico* novo = new NoHistorico;
    novo->produto = produto;
    novo->proximo = topo;
    topo = novo;
}

// Consulta o produto que está no topo da pilha.
// Parâmetros: topo (início da pilha) e produto (recebe o resultado).
// Retorno: true se encontrou um produto, false se a pilha estiver vazia.
bool consultarTopoHistorico(NoHistorico* topo, Produto& produto) {
    if (topo == nullptr) {
        return false;
    }

    produto = topo->produto;
    return true;
}

// Remove o produto que está no topo da pilha.
// Parâmetro: topo (referência ao início da pilha).
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
// Retorno: true se estiver vazia, false caso contrário.
bool pilhaVazia(NoHistorico* topo) {
    return topo == nullptr;
}

// Libera todos os nós da pilha.
// Parâmetro: topo (referência ao início da pilha).
// Retorno: nenhum.
void liberarPilha(NoHistorico*& topo) {
    while (topo != nullptr) {
    desempilharHistorico(topo);
    }
}
