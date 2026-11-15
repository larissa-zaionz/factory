#include <iostream>
#include "Menu.h"
#include "Factory.h"

using namespace std;

/**
 * Executa a acao da opcao escolhida no menu.
 * Parametros: opcao - valor ja validado; jogo - estado do jogo (alterado);
 *             rodando - controle do loop (vira false quando o jogador sai).
 * Retorno: nenhum.
 */
void tratarOpcao(int opcao, Jogo& jogo, bool& rodando) {
    switch (opcao) {
        case OPC_AVANCAR_TURNO:
            avancarTurno(jogo);
            break;
        case OPC_VER_PEDIDOS:
            verPedidos(jogo);
            break;
        case OPC_BUSCAR_PRODUTO:
            cout << "[TODO] buscar produto\n";
            break;
        case OPC_ENTREGAR_PEDIDO:
            cout << "[TODO] entregar pedido\n";
            break;
        case OPC_DESFAZER:
            cout << "[TODO] desfazer\n";
            break;
        case OPC_SAIR:
            rodando = false;
            break;
    }
}

/**
 * Ponto de entrada: repete "mostrar tela -> menu -> agir -> checar fim"
 * ate o jogador sair ou o prazo acabar.
 * Retorno: 0 se terminou normalmente.
 */
int main() {
    Jogo jogo;
    iniciarJogo(jogo);
    bool rodando = true;

    while (rodando) {
        mostrarTela(jogo);
        mostrarMenu();
        tratarOpcao(lerOpcao(), jogo, rodando);
        if (jogoTerminou(jogo)) {
            cout << "\nFim de jogo!\n";
            rodando = false;
        }
    }

    liberarMemoria(jogo);
    return 0;
}