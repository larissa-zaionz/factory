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