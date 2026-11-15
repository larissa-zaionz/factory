#ifndef ARVOREPRODUTOS_H
#define ARVOREPRODUTOS_H

#include <string>

struct Ingrediente {
    int idItem;
    int quantidade;
};

struct Receita {
    int id; // chave da BST
    std::string nome;
    Ingrediente ingredientes[4];
    int numIngredientes;
    int tempo; // turnos para produzir
};

struct NoArvore {
    Receita receita;
    NoArvore* esquerda;
    NoArvore* direita;
};

NoArvore* inserirReceita(NoArvore* raiz, const Receita& r);
NoArvore* buscarReceita(NoArvore* raiz, int id);
void mostrarInOrdem(const NoArvore* raiz);

#endif