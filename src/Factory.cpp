#include "Factory.h"
#include <iostream>

// Deixa a esteira vazia. Parametro: e (alterada). Retorno: nenhum.
void iniciarEsteira(Esteira& e) {
    e.inicio = nullptr;
    e.fim = nullptr;
}

// Coloca um produto no fim da esteira (usa enfileirar).
// Parametros: e (alterada) e p (copiado). Retorno: nenhum.
void colocarNaEsteira(Esteira& e, Produto p) {
    enfileirar(e.inicio, e.fim, p);
}

// Tira o produto da frente: consulta com frenteFila e remove com desenfileirar.
// Parametros: e (alterada) e p (recebe o produto). Retorno: false se vazia.
bool retirarDaEsteira(Esteira& e, Produto& p) {
    if (!frenteFila(e.inicio, p)) return false;
    desenfileirar(e.inicio, e.fim);
    return true;
}

// Mostra a esteira da frente para o fim, SEM remover nada.
// Parametro: e (so leitura). Retorno: nenhum.
void mostrarEsteira(const Esteira& e) {
    for (NoFila* a = e.inicio; a != nullptr; a = a->proximo) {
        std::cout << "[" << a->produto.nome << "]";
    }
    if (filaVazia(e.inicio)) std::cout << "(vazia)";
    std::cout << "\n";
}

// Libera todos os nos da esteira (usa liberarFila).
// Parametro: e (alterada). Retorno: nenhum.
void liberarEsteira(Esteira& e) {
    liberarFila(e.inicio, e.fim);
}

// Prepara o jogo: esteiras, maquinas, pedidos e historico, turno 1.
// Parametro: j (alterado). Retorno: nenhum.
void iniciarJogo(Jogo& j) {
    iniciarEsteira(j.esteira1);
    iniciarEsteira(j.esteira2);
    j.cortadora = criarMaquina("Cortadora", 2);
    j.montadora = criarMaquina("Montadora", 3);
    j.historico = nullptr;
    j.turno = 1;
    j.turnoMaximo = 20;
    criarPedidos(j);
}

// Desenha o estado do jogo (uma "foto" por turno), sem alterar nada.
// Parametro: j (so leitura). Retorno: nenhum.
void mostrarTela(const Jogo& j) {
    std::cout << "\n=== TURNO " << j.turno << " / " << j.turnoMaximo << " ===\n";
    std::cout << "Esteira 1: ";
    mostrarEsteira(j.esteira1);
    mostrarMaquina(j.cortadora);
    std::cout << "Esteira 2: ";
    mostrarEsteira(j.esteira2);
    mostrarMaquina(j.montadora);
}

// Executa um turno: entra material, cortadora, avanca o relogio.
// Parametro: j (alterado). Retorno: nenhum.
void avancarTurno(Jogo& j) {
    receberMateriaPrima(j);
    etapaCortadora(j);
    // TODO: etapaMontadora(j) quando o estoque existir
    j.turno++;
}

// Retorno: true quando o prazo de turnos acabou.
bool jogoTerminou(const Jogo& j) {
    return j.turno > j.turnoMaximo;
}

// Libera tudo que foi alocado (fecha o R4). Parametro: j (alterado).
void liberarMemoria(Jogo& j) {
    liberarEsteira(j.esteira1);
    liberarEsteira(j.esteira2);
    liberarPilha(j.historico);
}

// Cria uma maquina ociosa.
// Parametros: nome e tempo (turnos para produzir). Retorno: Maquina.
Maquina criarMaquina(const std::string& nome, int tempo) {
    return {nome, 0, tempo, false};
}

// Cria os pedidos iniciais (fora de ordem de prazo, de proposito).
// Parametro: j (alterado). Retorno: nenhum.
void criarPedidos(Jogo& j) {
    j.pedidos.push_back(criarPedido(1, "Carrinho", 3, 20));
    j.pedidos.push_back(criarPedido(2, "Carrinho", 1, 10));
    ordenarPedidos(j);
}

// Conta quantos produtos ha na esteira, sem remover nada.
// Parametro: e (so leitura). Retorno: quantidade.
int contarEsteira(const Esteira& e) {
    int total = 0;
    for (NoFila* a = e.inicio; a != nullptr; a = a->proximo) total++;
    return total;
}

// Mostra o estado de uma maquina (ociosa ou com progresso).
// Parametro: m (so leitura). Retorno: nenhum.
void mostrarMaquina(const Maquina& m) {
    std::cout << m.nome << ": ";
    if (m.ocupada)
        std::cout << "produzindo (" << m.progressoAtual << "/" << m.tempoNecessario << ")\n";
    else
        std::cout << "ociosa\n";
}

// Lista todos os pedidos (usa exibirPedido, da Pessoa C).
// Parametro: j (so leitura). Retorno: nenhum.
void verPedidos(const Jogo& j) {
    for (const Pedido& p : j.pedidos) exibirPedido(p);
}

// Coloca 1 Chapa na esteira 1.
// TEMPORARIO: depois vai tirar do estoque.
void receberMateriaPrima(Jogo& j) {
    colocarNaEsteira(j.esteira1, criarProduto(ID_CHAPA, "Chapa"));
}

// Se a cortadora esta livre e ha 3 chapas, consome as 3 e comeca a produzir.
// Parametro: j. Retorno: true se comecou.
bool alimentarCortadora(Jogo& j) {
    if (j.cortadora.ocupada || contarEsteira(j.esteira1) < 3) return false;
    Produto descartado = {0, ""};
    for (int i = 0; i < 3; i++) retirarDaEsteira(j.esteira1, descartado);
    j.cortadora.ocupada = true;
    j.cortadora.progressoAtual = 0;
    return true;
}

// Soma 1 turno de trabalho. Parametro: m.
// Retorno: true se terminou neste turno (a maquina volta a ficar livre).
bool avancarMaquina(Maquina& m) {
    if (!m.ocupada) return false;
    m.progressoAtual++;
    if (m.progressoAtual < m.tempoNecessario) return false;
    m.ocupada = false;
    m.progressoAtual = 0;
    return true;
}

// Etapa da cortadora: alimenta, trabalha e, se terminou,
// coloca uma Engrenagem na esteira 2. Parametro: j .
void etapaCortadora(Jogo& j) {
    alimentarCortadora(j);
    if (avancarMaquina(j.cortadora))
        colocarNaEsteira(j.esteira2, criarProduto(ID_ENGRENAGEM, "Engrenagem"));
}

// Ordena os pedidos por prazo (Insertion Sort da Pessoa C, R9).
// Parametro: j (alterado). Retorno: nenhum.
void ordenarPedidos(Jogo& j) {
    ordenarPedidosPorPrazo(j.pedidos);
}