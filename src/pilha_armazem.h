#ifndef PILHA_ARMAZEM_H
#define PILHA_ARMAZEM_H

#include <string>

struct NoPilha {
    std::string produto;
    NoPilha* proximo;
};

// Adiciona um produto no topo
void push(NoPilha*& topo, std::string produto);

// Consulta o produto do topo
std::string peek(NoPilha* topo);

// Remove o produto do topo
void pop(NoPilha*& topo);

// Verifica se a pilha está vazia
bool pilhaVazia(NoPilha* topo);

// Libera toda a memória da pilha
void liberarPilha(NoPilha*& topo);

#endif