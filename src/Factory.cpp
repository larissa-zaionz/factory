#include "Factory.h"
#include <iostream>
#include "Menu.h"

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
    j.receitas = nullptr;
    carregarReceitas(j);
    carregarEstoque(j);
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
    std::cout << "Estoque:\n";
    mostrarLista(j.estoque);
}

// Executa um turno: entra material, cortadora, avanca o relogio.
// Parametro: j (alterado). Retorno: nenhum.
void avancarTurno(Jogo& j) {
    receberMateriaPrima(j);
    etapaCortadora(j);
    etapaMontadora(j);
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
    liberarArvore(j.receitas);
    liberarLista(j.estoque);
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

// Lista os pedidos e, para os pendentes, a materia-prima necessaria.
// Parametro: j (so leitura). Retorno: nenhum.
void verPedidos(const Jogo& j) {
    for (const Pedido& p : j.pedidos) {
        exibirPedido(p);
        // TODO(C): trocar ID_CARRINHO por p.idProduto quando existir
        if (!p.entregue) mostrarNecessidade(j, ID_CARRINHO, p.quantidade);
    }
}

// Move ate 2 Chapas do estoque para a esteira 1.
// Parametro: j (alterado). Retorno: nenhum.
void receberMateriaPrima(Jogo& j) {
    for (int i = 0; i < 2; i++) {
        if (removerEstoque(j.estoque, ID_CHAPA, 1))
            colocarNaEsteira(j.esteira1, criarProduto(ID_CHAPA, "Chapa"));
    }
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
// Insere as receitas na BST (R8): Engrenagem = 3 Chapas;
// Carrinho = 2 Engrenagens + 4 Parafusos. Parametro: j (alterado).
void carregarReceitas(Jogo& j) {
    Receita engrenagem = {ID_ENGRENAGEM, "Engrenagem", {{ID_CHAPA, 3}}, 1, 2};
    Receita carrinho = {ID_CARRINHO, "Carrinho",
                        {{ID_ENGRENAGEM, 2}, {ID_PARAFUSO, 4}}, 2, 3};
    j.receitas = inserirReceita(j.receitas, engrenagem);
    j.receitas = inserirReceita(j.receitas, carrinho);
}

// Mostra a materia-prima total de qtd unidades do produto (recursao da Pessoa B, R3).
// Parametros: j (so leitura), idProduto, qtd. Retorno: nenhum.
void mostrarNecessidade(const Jogo& j, int idProduto, int qtd) {
    int totais[MAX_ID] = {0};
    calcularMateriaPrima(j.receitas, idProduto, qtd, totais);
    std::cout << "  Precisa de: " << totais[ID_CHAPA] << " Chapas e "
              << totais[ID_PARAFUSO] << " Parafusos\n";
}

// Cria o estoque inicial (lista encadeada, R5). Parametro: j (alterado).
void carregarEstoque(Jogo& j) {
    iniciarLista(j.estoque);
    adicionarEstoque(j.estoque, ID_CHAPA, 30);
    adicionarEstoque(j.estoque, ID_PARAFUSO, 20);
}

// Se a montadora esta livre, ha 2 engrenagens na esteira 2 e 4 parafusos
// no estoque, consome tudo e comeca a produzir.
// Parametro: j (alterado). Retorno: true se comecou.
bool alimentarMontadora(Jogo& j) {
    if (j.montadora.ocupada || contarEsteira(j.esteira2) < 2) return false;
    if (!removerEstoque(j.estoque, ID_PARAFUSO, 4)) return false;
    Produto descartado = {0, ""};
    for (int i = 0; i < 2; i++) retirarDaEsteira(j.esteira2, descartado);
    j.montadora.ocupada = true;
    j.montadora.progressoAtual = 0;
    return true;
}

// Etapa da montadora: alimenta, trabalha e, se terminou,
// guarda 1 Carrinho no estoque. Parametro: j (alterado).
void etapaMontadora(Jogo& j) {
    alimentarMontadora(j);
    if (avancarMaquina(j.montadora))
        adicionarEstoque(j.estoque, ID_CARRINHO, 1);
}

// Procura um pedido pelo ID. Parametros: j e idPedido.
// Retorno: ponteiro para o pedido, ou nullptr se nao existir.
Pedido* buscarPedido(Jogo& j, int idPedido) {
    for (Pedido& p : j.pedidos) {
        if (p.id == idPedido) return &p;
    }
    return nullptr;
}

// Entrega um pedido inteiro: tira os Carrinhos do estoque e empilha no historico.
// Retorno: false se o pedido nao existe, ja foi entregue ou falta produto.
bool entregarPedido(Jogo& j, int idPedido) {
    Pedido* p = buscarPedido(j, idPedido);
    if (p == nullptr || p->entregue) return false;
    if (!removerEstoque(j.estoque, ID_CARRINHO, p->quantidade)) return false;
    p->entregue = true;
    push(j.historico, criarProduto(p->id, p->produto));
    return true;
}

// Desfaz a ultima entrega (LIFO, R6): devolve os Carrinhos ao estoque
// e reabre o pedido. Retorno: false se nao ha nada para desfazer.
bool desfazerEntrega(Jogo& j) {
    Produto registro;
    if (!peek(j.historico, registro)) return false;
    Pedido* p = buscarPedido(j, registro.id);
    if (p != nullptr) {
        p->entregue = false;
        adicionarEstoque(j.estoque, ID_CARRINHO, p->quantidade);
    }
    pop(j.historico);
    return true;
}

// Opcao do menu: lista os pedidos e pergunta qual entregar (0 cancela).
// Parametro: j (alterado). Retorno: nenhum.
void acaoEntregar(Jogo& j) {
    verPedidos(j);
    std::cout << "Numero do pedido (0 cancela): ";
    int id = lerOpcao(0, static_cast<int>(j.pedidos.size()));
    if (id == 0) return;
    if (entregarPedido(j, id)) std::cout << "Pedido entregue!\n";
    else std::cout << "Nao foi possivel entregar (falta Carrinho no estoque?).\n";
}

// Opcao do menu: desfaz a ultima entrega. Parametro: j (alterado).
void acaoDesfazer(Jogo& j) {
    if (desfazerEntrega(j)) std::cout << "Ultima entrega desfeita.\n";
    else std::cout << "Nada para desfazer.\n";
}