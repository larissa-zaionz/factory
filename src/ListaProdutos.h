#ifndef LISTAPRODUTOS_H
#define LISTAPRODUTOS_H

struct NoLista {
    int idItem;
    int quantidade;
    NoLista* proximo;
};

struct Lista {
    NoLista* inicio;
    int tamanho;
};

void iniciarLista(Lista& l);
void adicionarEstoque(Lista& l, int idItem, int qtd);
bool removerEstoque(Lista& l, int idItem, int qtd);

#endif