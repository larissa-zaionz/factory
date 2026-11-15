#include "ListaProdutos.h"
#include <iostream>

// Procura o nó de um item e retorna o nó ou nullptr (se não existir).
// "static" é para ser visível apenas dentro desse arquivo.
static NoLista* buscarNo(const Lista& l, int idItem) {
    for (NoLista* a = l.inicio; a != nullptr; a = a->proximo) {
        if (a->idItem == idItem) return a;
    }
    return nullptr;
}

// Inicializa a lista vazia. O parâmetro é a referência de uma Lista l.
void iniciarLista(Lista& l) {
    l.inicio = nullptr;
    l.tamanho = 0;
}