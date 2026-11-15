#include "Produto.h"
#include "PilhaHistorico.h"

const int MAX_PEDIDOS = 10;

// IDs provisorios; trocar pelos da Pessoa C/B se eles definirem outros.
const int ID_CHAPA      = 10;
const int ID_PARAFUSO   = 11;
const int ID_ENGRENAGEM = 1;
const int ID_CARRINHO   = 2;

struct Jogo {
    Esteira esteira1;
    Esteira esteira2;
    Maquina cortadora;
    Maquina montadora;
    Pedido pedidos[MAX_PEDIDOS];
    int numPedidos;
    NoHistorico* historico;   // pilha de entregas (desfazer)
    int turno;
    int turnoMaximo;
    // TODO(B): Lista estoque;  NoArvore* receitas;
};