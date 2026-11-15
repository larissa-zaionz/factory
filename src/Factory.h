#ifndef FACTORY_H
#define FACTORY_H

#include "FilaProducao.h"
#include "PilhaHistorico.h"
#include <vector>
#include "Produto.h"

// Uma esteira = os dois ponteiros da fila agrupados numa struct.
struct Esteira {
    NoFila* inicio;
    NoFila* fim;
};

const int MAX_ID = 12;   // tamanho de vetores indexados por ID (maior ID = 11)

// IDs provisorios;
const int ID_CHAPA      = 10;
const int ID_PARAFUSO   = 11;
const int ID_ENGRENAGEM = 1;
const int ID_CARRINHO   = 2;

struct Jogo {
    Esteira esteira1;
    Esteira esteira2;
    Maquina cortadora;
    Maquina montadora;
    std::vector<Pedido> pedidos;
    NoHistorico* historico;   // pilha de entregas (desfazer)
    int turno;
    int turnoMaximo;
};

// Esteira
void iniciarEsteira(Esteira& e);
void colocarNaEsteira(Esteira& e, Produto p);
bool retirarDaEsteira(Esteira& e, Produto& p);
void mostrarEsteira(const Esteira& e);
void liberarEsteira(Esteira& e);

// Jogo
void iniciarJogo(Jogo& j);
void mostrarTela(const Jogo& j);
void avancarTurno(Jogo& j);
bool jogoTerminou(const Jogo& j);
void liberarMemoria(Jogo& j);

// Maquinas e pedidos
Maquina criarMaquina(const std::string& nome, int tempo);
void criarPedidos(Jogo& j);

// Exibicao
int contarEsteira(const Esteira& e);
void mostrarMaquina(const Maquina& m);
void verPedidos(const Jogo& j);

#endif