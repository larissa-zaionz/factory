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

// Inicializa a lista vazia. 
// Parâmetro: a referência de uma Lista l.
// Retorno: nenhum. (void)
void iniciarLista(Lista& l) {
    l.inicio = nullptr;
    l.tamanho = 0;
}

// Soma qtd ao item. Caso não exista, um nó novo é criado no inicio (new).
// Parâmetro: uma Lista l, idItem, qtd.
// Retorno: nenhum. (void)
void adicionarEstoque(Lista& l, int idItem, int qtd) {
    NoLista* no = buscarNo(l, idItem);
    if (no != nullptr) {
        no->quantidade += qtd;
        return;
    }
    NoLista* novo = new NoLista;
    novo->idItem = idItem;
    novo->quantidade = qtd;
    novo->proximo = l.inicio; // o novo nó aponta para o antigo "primeiro"
    l.inicio = novo; // a lista passa a começar no novo nó
    l.tamanho++;
}

// Tira qtd do item. Se zerar, a função remove o nó (delete).
// Parâmetro: uma Lista l, idItem, qtd.
// Retorno: false se o item não existe ou não tem quantidade suficiente.
bool removerEstoque(Lista& l, int idItem, int qtd) {
    NoLista* anterior = nullptr;
    NoLista* atual = l.inicio;
    while (atual != nullptr && atual->idItem != idItem) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == nullptr || atual->quantidade < qtd) return false;
    atual->quantidade -= qtd;
    if (atual->quantidade == 0) {
        if (anterior == nullptr) l.inicio = atual->proximo;
        else anterior->proximo = atual->proximo;
        delete atual;
        atual = nullptr;
        l.tamanho--;
    }
    return true;
}

// Essa função vai retornar a quantidade em estoque de certo item.
// Parâmetro: uma Lista l, idItem.
// Retorno: a quantidade em estoque (e 0 se não existir).
int quantidadeEstoque(const Lista& l, int idItem) {
    NoLista* no = buscarNo(l, idItem);
    return (no != nullptr) ? no->quantidade : 0;
}

// Já essa percorre a lista SEM REMOVER nada (veja o const) e imprime cada item.
// Parâmetro: uma Lista l.
// Retorno: nenhum. (void) (mas demonstra o conteúdo através de um cout)
void mostrarLista(const Lista& l) {
    for (NoLista* a = l.inicio; a != nullptr; a = a->proximo) {
        std::cout << "ID " << a->idItem << ": " << a->quantidade << "\n";
    }
    if (l.inicio == nullptr) std::cout  << "(estoque VAZIO)\n";
}

// Por fim, delete massivo em todos os nós e deixa a lista vazia.
// Parâmetro: uma Lista l.
// Retorno: nenhum. (void)
void liberarLista(Lista& l) {
    NoLista* atual = l.inicio;
    while (atual != nullptr) {
        NoLista* proximo = atual->proximo; // guardando antes de apagar, para seguir em frente depois
        delete atual;
        atual = proximo;
    }
    l.inicio = nullptr;
    l.tamanho = 0;
}