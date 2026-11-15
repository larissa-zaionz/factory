
#include "FilaProducao.h"

// Adiciona um produto no final da fila.
// Parâmetros: inicio e fim (referências aos nós da fila) e produto.
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
// Parâmetros: inicio e fim (referências aos nós da fila).
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
// Parâmetros: inicio (início da fila) e produto (recebe o resultado).
// Retorno: true se encontrou um produto, false se a fila estiver vazia.
bool frenteFila(NoFila* inicio, Produto& produto) {
    if (inicio == nullptr) {
        return false;
    }

    produto = inicio->produto;
    return true;
}

// Verifica se a fila está vazia.
// Parâmetro: inicio (início da fila).
// Retorno: true se estiver vazia, false caso contrário.
bool filaVazia(NoFila* inicio) {
    return inicio == nullptr;
}

// Libera toda a memória ocupada pela fila.
// Parâmetros: inicio e fim (referências aos nós da fila).
// Retorno: nenhum.
void liberarFila(NoFila*& inicio, NoFila*& fim) {
    while (inicio != nullptr) {
        desenfileirar(inicio, fim);
    }
}
