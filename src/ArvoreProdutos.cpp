#include "ArvoreProdutos.h"
#include <iostream>

// A primeira função daqui insere uma receita pela chave id recursivamente.
// Parâmetro: raiz (da árvore), uma Receita r.
// Retorno: a raiz da (sub)árvore.
NoArvore* inserirReceita(NoArvore* raiz, const Receita& r) {
    if (raiz == nullptr) {
        NoArvore* novo = new NoArvore;
        novo->receita = r;
        novo->esquerda = nullptr;
        novo->direita = nullptr;
        return novo;
    }
    if (r.id < raiz->receita.id)
        raiz->esquerda = inserirReceita(raiz->esquerda, r);
    else if (r.id > raiz->receita.id)
        raiz->direita = inserirReceita(raiz->direita, r);
    return raiz;
}

// Busca por id recursivamente.
// Parâmetro: raiz (da árvore), id.
// Retorno: o nó ou nullptr se não existir.
NoArvore* buscarReceita(NoArvore* raiz, int id) {
    if (raiz == nullptr || raiz->receita.id == id) return raiz;
    if (id < raiz->receita.id) return buscarReceita(raiz->esquerda, id);
    return buscarReceita(raiz->direita, id);
}

// Mostra as receitas em ordem crescente de id (esquerda, nó, direita).
// Parâmetro: raiz (da árvore).
// Retorno: nenhum. (void)
void mostrarInOrdem(const NoArvore* raiz) {
    if (raiz == nullptr) return;
    mostrarInOrdem(raiz->esquerda);
    std::cout << raiz->receita.id << " - " << raiz->receita.nome << "\n";
    mostrarInOrdem(raiz->direita);
}