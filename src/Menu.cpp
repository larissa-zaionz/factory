#include "Menu.h"
#include <iostream>
#include <limits>

using namespace std;

/**
 * Mostra as opcoes do menu principal.
 * Parametros: nenhum. Retorno: nenhum.
 */
void mostrarMenu() {
    cout << "1) Avancar turno   2) Ver pedidos   3) Buscar produto\n";
    cout << "4) Entregar pedido 5) Desfazer      0) Sair\n";
    cout << "> ";
}

/**
 * Le uma opcao do teclado e repete ate ela ser valida.
 * Parametros: minimo e maximo (valor por padrao: 0 e 5).
 * Retorno: a opcao valida; 0 (sair) se a entrada acabar.
 */
int lerOpcao(int minimo, int maximo) {
    int opcao;
    while (true) {
        if (cin >> opcao && opcao >= minimo && opcao <= maximo) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return opcao;
        }
        if (cin.eof()) return 0;  // sem isso, o loop travaria
        cin.clear();                                         // tira o cin do estado de erro
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descarta a linha inteira
        cout << "Opcao invalida. Tente de novo: ";
    }
}