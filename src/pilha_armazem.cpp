
#include "pilha_armazem.h"

// Adiciona um produto no topo da pilha.
// Parâmetros: topo (referência para o início) e produto (nome).
// Retorno: nenhum.
void push(NoPilha*& topo, std::string produto) {
    NoPilha* novo = new NoPilha;
    novo->produto = produto;
    novo->proximo = topo;
    topo = novo;
}

// Consulta o produto que está no topo.
// Parâmetros: topo (início da pilha).
// Retorno: nome do produto ou texto vazio.
std::string peek(NoPilha* topo) {
    if (topo == nullptr) {
        return "";
    }

    return topo->produto;
}

// Remove o produto que está no topo.
// Parâmetros: topo (referência para o início).
// Retorno: nenhum.
void pop(NoPilha*& topo) {
    if (topo == nullptr) {
        return;
    }

    NoPilha* auxiliar = topo;
    topo = topo->proximo;
    delete auxiliar;
}

// Verifica se a pilha está vazia.
// Parâmetros: topo (início da pilha).
// Retorno: true se vazia, false caso contrário.
bool pilhaVazia(NoPilha* topo) {
    return topo == nullptr;
}

// Libera todos os produtos da pilha.
// Parâmetros: topo (referência para o início).
// Retorno: nenhum.
void liberarPilha(NoPilha*& topo) {
    while (topo != nullptr) {
        pop(topo);
    }
}
