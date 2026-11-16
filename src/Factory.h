#ifndef FACTORY_H
#define FACTORY_H

#include "FilaProducao.h"
#include "PilhaHistorico.h"
#include <vector>
#include "Produto.h"
#include "Ordenacao.h"
#include "ArvoreProdutos.h"
#include "ListaProdutos.h"
#include "Busca.h"
// Uma esteira = os dois ponteiros da fila agrupados numa struct.
struct Esteira {
    NoFila* inicio;
    NoFila* fim;
};

const int MAX_ID = 12;   // tamanho de vetores indexados por ID (maior ID = 11)

// IDs;
const int ID_CHAPA      = 10;
const int ID_PARAFUSO   = 11;
const int ID_ENGRENAGEM = 1;
const int ID_CARRINHO   = 2;
const int CAPACIDADE_ESTEIRA = 4;   // maximo de pecas na esteira 1

struct Jogo {
    Esteira esteira1;
    Esteira esteira2;
    Maquina cortadora;
    Maquina montadora;
    std::vector<Pedido> pedidos;
    NoHistorico* historico;   // pilha de entregas (desfazer)
    NoArvore* receitas;       // raiz da BST de receitas
    Lista estoque;            // materia-prima e produtos prontos
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

// Turno
void receberMateriaPrima(Jogo& j);
bool alimentarCortadora(Jogo& j);
bool avancarMaquina(Maquina& m);
void etapaCortadora(Jogo& j);

// Ordenação
void ordenarPedidos(Jogo& j);

// Receitas
void carregarReceitas(Jogo& j);
void mostrarNecessidade(const Jogo& j, int idProduto, int qtd);

// Estoque e montadora
void carregarEstoque(Jogo& j);
bool alimentarMontadora(Jogo& j);
void etapaMontadora(Jogo& j);

// Entrega e desfazer
Pedido* buscarPedido(Jogo& j, int idPedido);
bool entregarPedido(Jogo& j, int idPedido);
bool desfazerEntrega(Jogo& j);
void acaoEntregar(Jogo& j);
void acaoDesfazer(Jogo& j);

// BST
void arvoreParaVetor(const NoArvore* raiz, std::vector<Produto>& v);
std::vector<Produto> montarCatalogo(const Jogo& j);
void acaoBuscar(const Jogo& j);

// Fim do jogo
bool todosEntregues(const Jogo& j);
void mostrarResultado(const Jogo& j);

std::string nomeDoItem(int idItem);
void mostrarEstoque(const Jogo& j);
void mostrarParafusos(const Jogo& j);
bool esteiraCheia(const Esteira& e);

bool pedidoVencido(const Jogo& j, const Pedido& p);
bool todosResolvidos(const Jogo& j);

#endif