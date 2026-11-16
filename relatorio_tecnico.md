================================================================================
RELATÓRIO TÉCNICO — SIMULADOR DE FÁBRICA DE CARRINHOS DE BRINQUEDO (C++17)
================================================================================

1. IDENTIFICAÇÃO E OBJETIVO DO PROJETO
--------------------------------------------------------------------------------
Projeto: Simulador de Linha de Produção Industrial (Fábrica de Carrinhos)
Linguagem: C++17 (execução via terminal)
Integrantes e Divisão de Módulos:
- João Gabriel (Pessoa A): Estruturas Lineares Dinâmicas (FilaProducao, PilhaHistorico)
- João Augusto (Pessoa B): Armazenamento e Hierarquia (ListaProdutos, ArvoreProdutos)
- Larissa Zaionz (Pessoa C): Modelagem de Dados, Ordenação e Busca (Produto, Ordenacao, Busca)
- Lucas Kruppa (Pessoa D): Motor do Jogo e Interface (Factory, Menu, main)

Objetivo:
Desenvolver um simulador interativo baseado em turnos no qual o jogador gerencia
uma linha de produção de carrinhos de brinquedo. O sistema aplica na prática
estruturas de dados fundamentais (Fila, Pilha, Lista Encadeada e Árvore) e
algoritmos clássicos de ordenação e busca, mantendo baixo acoplamento modular,
segurança de memória e compatibilidade multiplataforma (Linux/WSL e Windows).


2. ARQUITETURA MODULAR E ESTRUTURAS DE DADOS
--------------------------------------------------------------------------------
O projeto foi dividido em módulos independentes (.h e .cpp) dentro do diretório
src/, permitindo que cada integrante desenvolvesse e testasse suas estruturas
sem conflitos de dependência:

2.1. Esteira de Produção e Histórico (João Gabriel — Pessoa A)
- FilaProducao (Fila — FIFO: First-In, First-Out):
  Gerencia as peças e componentes em processamento na linha de montagem. Garante
  que os itens entrem e saiam das estações de trabalho estritamente na ordem em
  que foram inseridos, simulando o fluxo contínuo de uma esteira industrial.
- PilhaHistorico (Pilha — LIFO: Last-In, First-Out):
  Armazena o registro das últimas entregas e ações concluídas pelo jogador.
  Permite reverter a operação mais recente (funcionalidade de desfazer/undo)
  acessando diretamente o topo da estrutura em tempo constante O(1).

2.2. Controle de Estoque e Receitas de Montagem (João Augusto — Pessoa B)
- ListaProdutos (Lista Encadeada):
  Mantém o inventário dinâmico de peças e brinquedos disponíveis na fábrica.
  Permite inserções e remoções flexíveis conforme matérias-primas são
  consumidas na montagem e novos carrinhos são finalizados.
- ArvoreProdutos (Árvore Hierárquica):
  Representa a árvore de montagem (receitas/BOM - Bill of Materials) dos
  produtos. O nó raiz representa o produto final ("Carrinho") e seus nós
  filhos representam os subcomponentes necessários ("Chapa", "Parafuso",
  "Engrenagem"), facilitando a validação de requisitos antes da fabricação.

2.3. Modelagem de Dados, Ordenação e Busca (Larissa Zaionz — Pessoa C)
- Estruturas Base (Produto.h / Produto.cpp):
  Define as structs compartilhadas por todo o sistema:
  * Produto: identificador numérico (id) e descrição (nome).
  * Maquina: nome da estação, progressoAtual, tempoNecessario e estado ocupada.
  * Pedido: id, produto solicitado, quantidade, prazoTurno e status entregue.
  As funções auxiliares utilizam passagem por referência constante (const &)
  para evitar cópias desnecessárias de strings e structs na memória.
- Ordenação de Pedidos (Ordenacao.h / Ordenacao.cpp — Insertion Sort):
  Ordena a fila/lista de pedidos pendentes em ordem crescente de prazoTurno,
  priorizando as entregas mais urgentes.
- Pesquisa no Catálogo (Busca.h / Busca.cpp — Busca Sequencial e Binária):
  Implementa dois mecanismos de consulta retornando a struct ResultadoBusca
  (índice encontrado e contador exato de comparações realizadas):
  * buscarPorNomeSequencial: percorre o catálogo comparando nomes.
  * buscarPorIdBinaria: localiza produtos pelo ID em catálogo ordenado.

2.4. Motor da Simulação e Interface (Lucas Kruppa — Pessoa D)
- Factory (Factory.h / Factory.cpp):
  Orquestra o ciclo de turnos da fábrica, integrando o catálogo de produtos,
  o avanço das máquinas, o consumo de estoque na ListaProdutos, a validação
  na ArvoreProdutos, a ordenação dos pedidos e o registro no PilhaHistorico.
- Menu e main (Menu.h / Menu.cpp / main.cpp):
  Gerencia o loop principal da aplicação, exibição dos estados das estruturas
  no terminal, leitura validada de entradas do usuário e encerramento limpo.


3. ANÁLISE DE COMPLEXIDADE ASSINTÓTICA (ALGORITMOS E OPERAÇÕES)
--------------------------------------------------------------------------------
A escolha de cada algoritmo e estrutura baseou-se no comportamento real dos
dados durante os turnos do simulador:

Algoritmo / Operação         | Melhor Caso | Caso Médio  | Pior Caso   | Espaço
-----------------------------|-------------|-------------|-------------|--------
Insertion Sort (Pedidos)     | O(n)        | O(n^2)      | O(n^2)      | O(1)
Busca Sequencial (por Nome)  | O(1)        | O(n)        | O(n)        | O(1)
Busca Binária (por ID)       | O(1)        | O(log n)    | O(log n)    | O(1)
Fila: Enfileirar/Desenfil.   | O(1)        | O(1)        | O(1)        | O(1)
Pilha: Empilhar/Desempilhar  | O(1)        | O(1)        | O(1)        | O(1)

Justificativas Técnicas:
- Por que Insertion Sort?
  A cada turno, apenas poucos pedidos novos são adicionados a uma lista que já
  se encontra ordenada. Em vetores pequenos e parcialmente ordenados, o
  Insertion Sort opera próximo de O(n), é estável (preserva a ordem de chegada
  em caso de empate no prazoTurno) e não exige memória auxiliar extra O(1).
- Por que Busca Sequencial vs. Busca Binária?
  O catálogo é cadastrado em ordem crescente de ID, permitindo que a Busca
  Binária descarte metade dos elementos a cada passo — O(log n). Já a pesquisa
  por nome não segue ordem alfabética fixa, exigindo a Busca Sequencial — O(n).
  O contador de comparações em ResultadoBusca permite comprovar empiricamente
  essa diferença de desempenho durante a execução do programa.


4. INFRAESTRUTURA DE BUILD, PORTABILIDADE E MEMÓRIA
--------------------------------------------------------------------------------
Para garantir que todos os integrantes pudessem compilar e testar o projeto
em diferentes sistemas operacionais sem alterações manuais de código, foram
adotadas as seguintes práticas de engenharia de software:

4.1. Automação Multiplataforma (Makefile)
- Compilação com g++ -std=c++17 -Wall -Wextra -g para capturar avisos e
  facilitar a depuração.
- Uso da função $(wildcard src/*.cpp) e $(wildcard src/*.h), permitindo que
  novos módulos sejam compilados automaticamente sem editar o Makefile.
- Detecção automática de sistema operacional via variável OS (Windows_NT):
  ajusta o nome do binário (factory no Linux/WSL vs. factory.exe no Windows)
  e os comandos de limpeza (rm -f vs. del /Q /F).

4.2. Padronização de Fim de Linha (.gitattributes)
- Durante o desenvolvimento colaborativo entre Windows e Linux, identificou-se
  o erro "missing separator" no GNU Make causado por quebras de linha CRLF
  (\r\n) geradas no Windows.
- A inclusão do arquivo .gitattributes com a diretiva "Makefile text eol=lf"
  forçou o Git a preservar quebras de linha Unix (LF) no Makefile em qualquer
  ambiente, eliminando falhas de compilação entre os membros da equipe.

4.3. Verificação de Integridade de Memória (AddressSanitizer)
- O alvo "make asan" compila o projeto com as flags -fsanitize=address e
  -fsanitize=undefined em ambiente Linux/WSL, assegurando que todas as
  alocações dinâmicas nas estruturas encadeadas (Fila, Pilha, Lista e Árvore)
  sejam devidamente liberadas ao encerrar o programa, sem vazamentos de memória
  (memory leaks) ou acessos inválidos.


5. CONCLUSÃO
--------------------------------------------------------------------------------
A arquitetura modular adotada permitiu integrar com sucesso quatro estruturas
de dados clássicas e três algoritmos de ordenação e busca em um simulador
funcional e coeso. A separação clara de responsabilidades via arquivos de
cabeçalho (.h), aliada à automação de build multiplataforma e à verificação
com AddressSanitizer, garantiu estabilidade, portabilidade e facilidade de
manutenção ao longo de todo o desenvolvimento.
================================================================================