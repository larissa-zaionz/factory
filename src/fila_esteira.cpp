#include "fila_esteira.h"

// Adiciona um produto no final da fila.
// Parâmetros: início, fim e nome do produto.
// Retorno: nenhum.
void enfileirar(NoFila*& inicio, NoFila*& fim, std::string produto) {
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
// Parâmetros: início e fim da fila.
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

// Consulta o primeiro produto.
// Parâmetro: início da fila.
// Retorno: nome do produto ou texto vazio.
std::string frenteFila(NoFila* inicio) {
    if (inicio == nullptr) {
        return "";
    }

    return inicio->produto;
}

// Verifica se a fila está vazia.
// Parâmetro: início da fila.
// Retorno: true se vazia, false caso contrário.
bool filaVazia(NoFila* inicio) {
    return inicio == nullptr;
}

// Libera toda a memória da fila.
// Parâmetros: início e fim da fila.
// Retorno: nenhum.
void liberarFila(NoFila*& inicio, NoFila*& fim) {
    while (inicio != nullptr) {
        desenfileirar(inicio, fim);
    }
}