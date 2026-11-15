#ifndef BUSCA_H
#define BUSCA_H

#include <string>
#include <vector>
#include "Produto.h"

struct ResultadoBusca {
    int indice;
    int comparacoes;
};

ResultadoBusca buscarPorNomeSequencial(const std::vector<Produto>& lista, const std::string& nome);
ResultadoBusca buscarPorIdBinaria(const std::vector<Produto>& listaOrdenada, int id);

#endif