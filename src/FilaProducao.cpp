
#include "FilaProducao.h"

// Adiciona um produto no final da fila.
// Parâmetros: início, fim e produto.
// Retorno: nenhum.
void enfileirar(NoFila*& inicio, NoFila*& fim, Produto produto) {
    NoFila* novo = new NoFila;
    novo->produto = produto;
    novo->proximo = nullptr;

    if (inicio == nullptr) {
        inicio = novo;
        fim = novo;
    } else {
        fim->proximo = novo;
        fim = novo;
    }
}

// Remove o primeiro produto da fila.
// Parâmetros: início e fim.
// Retorno: nenhum.
void desenfileirar(NoFila*& inicio, NoFila*& fim) {
    if (inicio == nullptr) {
        return;
    }

    NoFila* auxiliar = inicio;
    inicio = inicio->proximo;

    if (inicio == nullptr) {
        fim = nullptr;
    }

    delete auxiliar;
}

// Consulta o primeiro produto da fila.
// Parâmetros: início e produto.
// Retorno: true se encontrou um produto.
bool frenteFila(NoFila* inicio, Produto& produto) {
    if (inicio == nullptr) {
        return false;
    }

    produto = inicio->produto;
    return true;
}

// Verifica se a fila está vazia.
// Parâmetro: início.
// Retorno: true se vazia.
bool filaVazia(NoFila* inicio) {
    return inicio == nullptr;
}

// Libera toda a memória da fila.
// Parâmetros: início e fim.
// Retorno: nenhum.
void liberarFila(NoFila*& inicio, NoFila*& fim) {
    while (inicio != nullptr) {
        desenfileirar(inicio, fim);
    }
}
