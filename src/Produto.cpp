#include <iostream>
#include "Produto.h"

/*
 * Objetivo: Cria e retorna um novo produto ou peca automotiva.
 * Parametros: id (codigo unico), nome (nome da peca ou modelo do carro).
 * Retorno: Struct Produto preenchida.
 */
Produto criarProduto(int id, const std::string& nome) {
    return {id, nome};
}

/*
 * Objetivo: Cria e retorna um novo pedido de veiculos pendente.
 * Parametros: id (codigo), produto (modelo do carro), qtd (quantidade), prazo (turno limite).
 * Retorno: Struct Pedido preenchida.
 */
Pedido criarPedido(int id, const std::string& produto, int qtd, int prazo) {
    return {id, produto, qtd, prazo, false};
}

/*
 * Objetivo: Exibe os detalhes formatados de um pedido no terminal.
 * Parametros: p (referencia constante para o pedido).
 * Retorno: void.
 */
void exibirPedido(const Pedido& p) {
    std::cout << "[Pedido #" << p.id << "] " << p.produto
              << " x" << p.quantidade
              << " | Prazo: turno " << p.prazoTurno
              << " | Status: " << (p.entregue ? "ENTREGUE" : "PENDENTE") << "\n";
}