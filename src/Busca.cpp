#include "Busca.h"

/*
 * Objetivo: Busca um produto pelo nome percorrendo a lista item a item.
 * Parametros: lista (vetor de produtos), nome (texto buscado).
 * Retorno: Struct ResultadoBusca contendo o indice (-1 se nao achar) e as comparacoes.
 */
ResultadoBusca buscarPorNomeSequencial(const std::vector<Produto>& lista, const std::string& nome) {
    int comparacoes = 0;
    for (int i = 0; i < static_cast<int>(lista.size()); i++) {
        comparacoes++;
        if (lista[i].nome == nome) {
            return {i, comparacoes};
        }
    }
    return {-1, comparacoes};
}

/*
 * Objetivo: Busca um produto pelo ID dividindo o vetor ordenado ao meio.
 * Parametros: listaOrdenada (vetor ordenado por ID crescente), id (codigo buscado).
 * Retorno: Struct ResultadoBusca contendo o indice (-1 se nao achar) e as comparacoes.
 */
ResultadoBusca buscarPorIdBinaria(const std::vector<Produto>& listaOrdenada, int id) {
    int esquerda = 0, direita = static_cast<int>(listaOrdenada.size()) - 1;
    int comparacoes = 0;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoes++;
        if (listaOrdenada[meio].id == id) return {meio, comparacoes};
        if (listaOrdenada[meio].id < id) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return {-1, comparacoes};
}