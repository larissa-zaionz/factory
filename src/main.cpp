#include <iostream>
#include "Menu.h"

using namespace std;

/**
 * Executa a acao da opcao escolhida no menu.
 * Parametros: opcao - valor ja validado; rodando - referencia ao
 *             controle do loop (vira false quando o jogador sai).
 * Retorno: nenhum.
 */
void tratarOpcao(int opcao, bool& rodando) {
    switch (opcao) {
        case OPC_AVANCAR_TURNO:
            cout << "[TODO] avancar turno\n";
            break;
        case OPC_VER_PEDIDOS:
            cout << "[TODO] ver pedidos\n";
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
 * Ponto de entrada: repete "mostrar menu -> ler opcao -> agir"
 * ate o jogador escolher sair.
 * Retorno: 0 se terminou normalmente.
 */
int main() {
    bool rodando = true;

    while (rodando) {
        mostrarMenu();
        tratarOpcao(lerOpcao(), rodando);
    }

    cout << "Ate a proxima!\n";
    return 0;
}