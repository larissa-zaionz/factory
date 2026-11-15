#include "Ordenacao.h"

/*
 * Objetivo: Ordena a lista de pedidos por prazoTurno crescente usando Insertion Sort.
 * Parametros: pedidos (referencia para o vetor de pedidos a ser ordenado).
 * Retorno: void (modifica o vetor diretamente).
 *
 * Complexidade de Tempo:
 * - Melhor caso: O(n), quando os pedidos ja estao ordenados por prazo.
 * - Caso medio e pior caso: O(n^2), quando os pedidos chegam em ordem inversa.
 * Complexidade de Espaco: O(1), pois ordena no proprio vetor (in-place).
 */
void ordenarPedidosPorPrazo(std::vector<Pedido>& pedidos) {
    int n = static_cast<int>(pedidos.size());
    for (int i = 1; i < n; i++) {
        Pedido chave = pedidos[i];
        int j = i - 1;
        while (j >= 0 && pedidos[j].prazoTurno > chave.prazoTurno) {
            pedidos[j + 1] = pedidos[j];
            j--;
        }
        pedidos[j + 1] = chave;
    }
}