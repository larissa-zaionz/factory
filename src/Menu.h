#ifndef MENU_H
#define MENU_H

// Opcoes do menu principal (nomes no lugar de numeros "magicos")
enum OpcaoMenu {
    OPC_SAIR            = 0,
    OPC_AVANCAR_TURNO   = 1,
    OPC_VER_PEDIDOS     = 2,
    OPC_BUSCAR_PRODUTO  = 3,
    OPC_ENTREGAR_PEDIDO = 4,
    OPC_DESFAZER        = 5
};

// Valores padrao ficam SO na declaracao (.h), nunca na definicao (.cpp).
int lerOpcao(int minimo = 0, int maximo = 5);
void mostrarMenu();

#endif