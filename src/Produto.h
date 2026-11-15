#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

struct Produto {
    int id;        
    std::string nome;    
};

struct Maquina {
    std::string nome;  
    int progressoAtual;
    int tempoNecessario;
    bool ocupada;
};

struct Pedido {
    int id;              
    std::string produto;  
    int quantidade;       
    int prazoTurno;     
    bool entregue;       
};

Produto criarProduto(int id, const std::string& nome);
Pedido criarPedido(int id, const std::string& produto, int qtd, int prazo);
void exibirPedido(const Pedido& p);

#endif