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

// Delete massivo em todos os nós (começando pelos filhos) e nullifica o ponteiro.
// Parâmetro: raiz (da árvore).
// Retorno: nenhum. (void)
void liberarArvore(NoArvore*& raiz) {
    if (raiz == nullptr) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    delete raiz;
    raiz = nullptr;
}

// R3: soma em totais[] as matérias-primas de qtd unidades do item.
// Caso base: item sem receita na árvore = matéria-prima.
// Parâmetro: raiz (da árvore), idItem, qtd, totais[].
// Retorno: nenhum. (void)
void calcularMateriaPrima(NoArvore* raiz, int idItem, int qtd, int totais[]){
    NoArvore* no = buscarReceita(raiz, idItem);
    if (no == nullptr) {
        totais[idItem] += qtd;
        return;
    }
    for (int i = 0; i < no->receita.numIngredientes; i++) {
        Ingrediente ing = no->receita.ingredientes[i];
        calcularMateriaPrima(raiz, ing.idItem, qtd * ing.quantidade, totais);
    }
}