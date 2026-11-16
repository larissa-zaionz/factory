#  Simulador de Fábrica de Carrinhos de Brinquedo (C++)

Simulador de linha de produção industrial desenvolvido em **C++17** via terminal, focado na aplicação prática de **Estruturas de Dados** e **Algoritmos de Ordenação e Busca** para gerenciar a fabricação e entrega de carrinhos de brinquedo por turnos.

---

## Funcionalidades do Sistema

* **Linha de Produção (Fila - FIFO):** Processamento sequencial das peças na esteira (`Chapa`, `parafuso`,`Engrenagem`, `Carrinho`).
* **Histórico de Entregas (Pilha - LIFO):** Registro das últimas entregas concluídas com opção de desfazer a ação mais recente.
* **Estoque e Receitas (Lista e Árvore):** Gerenciamento de itens em estoque e consulta hierárquica dos componentes necessários para montar cada carrinho.
* **Priorização de Pedidos (Insertion Sort):** Ordenação automática das encomendas por prazo de entrega (`prazoTurno`) crescente.
* **Consulta de Catálogo (Busca Sequencial e Binária):** Pesquisa de peças/brinquedos por **Nome** ou por **ID**, exibindo em tempo real a quantidade de comparações realizadas por cada algoritmo.

---


## Arquitetura do Projeto

```text
factory/
├── src/
│   ├── main.cpp              # Ponto de entrada e loop principal
│   ├── Menu.h / .cpp         # Interface de interação no terminal
│   ├── Factory.h / .cpp      # Lógica central dos turnos e regras da fábrica
│   ├── FilaProducao.h/.cpp   # Estrutura de Fila (esteira de produção)
│   ├── PilhaHistorico.h/.cpp # Estrutura de Pilha (histórico / desfazer)
│   ├── ListaProdutos.h/.cpp  # Estrutura de Lista (controle de estoque)
│   ├── ArvoreProdutos.h/.cpp # Estrutura de Árvore (receitas de montagem)
│   ├── Produto.h / .cpp      # Structs base (Produto, Maquina, Pedido)
│   ├── Ordenacao.h / .cpp    # Algoritmo Insertion Sort para pedidos
│   └── Busca.h / .cpp        # Algoritmos de Busca Sequencial e Binária
├── Makefile                  # Automação de build (Linux e Windows)
└── README.md                 # Documentação do projeto
```
---

##  Equipe e Responsabilidades

**João Gabriel** (Pessoa A): Estruturas Lineares Dinâmicas — FilaProducao e PilhaHistorico

**João Augusto** (Pessoa B): Armazenamento e Hierarquia — ListaProdutos e ArvoreProdutos

**Larissa Zaionz** (Pessoa C): Modelagem de Dados (Produto), Ordenação (Insertion Sort) e Buscas (Sequencial e Binária)

**Lucas Kruppa** (Pessoa D): Motor do Jogo e Interface — Factory, Menu e main


## Como Compilar e Executar

O projeto conta com um `Makefile` multiplataforma (Linux, WSL e Windows/MinGW) e `.gitattributes` configurado para manter as quebras de linha em padrão `LF`.

> **Nota para Windows puro:** caso utilize MinGW sem WSL, substitua `make` por `mingw32-make` nos comandos abaixo.

- `make` — Compila o projeto (gera `factory` no Linux/WSL ou `factory.exe` no Windows)
- `make run` — Compila e executa o simulador
- `make asan` — Executa com verificação de memória via AddressSanitizer (Linux/WSL)
- `make clean` — Remove os executáveis compilados