#ifndef FILA_PRODUCAO_H
#define FILA_PRODUCAO_H

#include "Produto.h"

struct NoFila {
    Produto produto;
    NoFila* proximo;
};

// Adiciona um produto no final da fila.
void enfileirar(NoFila*& inicio, NoFila*& fim, Produto produto);

// Remove o primeiro produto da fila.
void desenfileirar(NoFila*& inicio, NoFila*& fim);

// Consulta o primeiro produto da fila.
bool frenteFila(NoFila* inicio, Produto& produto);

// Verifica se a fila está vazia.
bool filaVazia(NoFila* inicio);

// Libera toda a memória da fila.
void liberarFila(NoFila*& inicio, NoFila*& fim);

#endif