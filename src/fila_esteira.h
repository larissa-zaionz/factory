#ifndef FILA_ESTEIRA_H
#define FILA_ESTEIRA_H

#include <string>

struct NoFila {
    std::string produto;
    NoFila* proximo;
};

// Adiciona um produto no final da fila
void enfileirar(NoFila*& inicio, NoFila*& fim, std::string produto);

// Remove o primeiro produto da fila
void desenfileirar(NoFila*& inicio, NoFila*& fim);

// Consulta o primeiro produto
std::string frenteFila(NoFila* inicio);

// Verifica se a fila está vazia
bool filaVazia(NoFila* inicio);

// Libera toda a memória da fila
void liberarFila(NoFila*& inicio, NoFila*& fim);

#endif