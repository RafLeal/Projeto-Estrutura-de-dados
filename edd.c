#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura Paciente para armazenar informações de cada paciente
typedef struct Paciente {
  char nome[50];
  int idade;
  char RG[15];
  int dia;
  int mes;
  int ano;
  struct Paciente *prox; // Ponteiro para o próximo paciente na lista
} Paciente;

Paciente *lista_pacientes = NULL; // Inicialização da lista de pacientes

// Função para cadastrar um novo paciente na lista
void cadastro_novo(){
  
  Paciente *novo_paciente = (Paciente *)malloc(sizeof(Paciente));

  if (novo_paciente == NULL) {
    printf("Memória insuficiente.\n");
    return;
  }

  printf("Digite o nome do paciente: ");
  scanf(" %[^\n]s", novo_paciente->nome);
  printf("Digite a idade: ");
  scanf("%d", &novo_paciente->idade);
  printf("Digite o RG: ");
  scanf(" %[^\n]s", novo_paciente->RG);
  printf("Digite o dia de registro: ");
  scanf("%d", &novo_paciente->dia);
  printf("Digite o mês de registro: ");
  scanf("%d", &novo_paciente->mes);
  printf("Digite o ano de registro: ");
  scanf("%d", &novo_paciente->ano);

  novo_paciente->prox = NULL;

  // Inserção mantendo a ordem de registro
  if (lista_pacientes == NULL || novo_paciente->ano < lista_pacientes->ano ||
    (novo_paciente->ano == lista_pacientes->ano && novo_paciente->mes < lista_pacientes->mes) ||
    (novo_paciente->ano == lista_pacientes->ano && novo_paciente->mes == lista_pacientes->mes && novo_paciente->dia < lista_pacientes->dia)) {
    novo_paciente->prox = lista_pacientes;
    lista_pacientes = novo_paciente;
  } 
    
  else {
    Paciente *atual = lista_pacientes;
    while (atual->prox != NULL &&
      (atual->prox->ano < novo_paciente->ano ||
      (atual->prox->ano == novo_paciente->ano && atual->prox->mes < novo_paciente->mes) ||
      (atual->prox->ano == novo_paciente->ano && atual->prox->mes == novo_paciente->mes && atual->prox->dia < novo_paciente->dia))) {
      atual = atual->prox;
    }
    
    novo_paciente->prox = atual->prox;
    atual->prox = novo_paciente;
  }

  printf("\nNovo paciente cadastrado com sucesso!\n");
}

// Função para consultar as informações de um paciente a partir do RG
void consultar(){
  
  char rg_consulta[15];
  printf("Digite o RG do paciente para consultar: ");
  scanf(" %[^\n]s", rg_consulta);
  printf("\n");

  Paciente *atual = lista_pacientes;
  int encontrado = 0;

  while (atual != NULL) {
    if (strcmp(atual->RG, rg_consulta) == 0) {
      printf("Paciente encontrado:\n\n");
      printf("Nome: %s\n", atual->nome);
      printf("Idade: %d\n", atual->idade);
      printf("RG: %s\n", atual->RG);
      printf("Data de Registro: %d/%d/%d\n", atual->dia, atual->mes, atual->ano);
      encontrado = 1;
      break;
    }
    atual = atual->prox;
  }

  if (!encontrado) {
    printf("Paciente não encontrado com o RG informado.\n");
    
  }
}

// Função para exibir a lista de pacientes cadastrados
void lista_de_pacientes(){
  
  if (lista_pacientes == NULL) {
    printf("A lista de pacientes está vazia.\n\n");
    return;
  }

  Paciente *atual = lista_pacientes;
  printf("Lista de pacientes cadastrados:\n\n");

  while (atual != NULL) {
    printf("Nome: %s\n", atual->nome);
    printf("Idade: %d\n", atual->idade);
    printf("RG: %s\n", atual->RG);
    printf("Data de Registro: %d/%d/%d\n", atual->dia, atual->mes, atual->ano);
    printf("-------------------------\n");
    atual = atual->prox;
  }
}

// Função para atualizar os dados de um paciente baseado no RG
void atualizar_dados(){
  
  char rg_atualizar[15];
  printf("Digite o RG do paciente para atualizar os dados: ");
  scanf(" %[^\n]s", rg_atualizar);
  printf("\n");

  Paciente *atual = lista_pacientes;
  int encontrado = 0;

  while (atual != NULL) {
    if (strcmp(atual->RG, rg_atualizar) == 0) {
      printf("Paciente encontrado:\n");
      printf("Nome: %s\n", atual->nome);
      printf("Idade: %d\n", atual->idade);
      printf("RG: %s\n", atual->RG);
      printf("Data de Registro: %d/%d/%d\n", atual->dia, atual->mes, atual->ano);
      encontrado = 1;

      printf("\nDigite as novas informações do paciente:\n");
      printf("Novo nome: ");
      scanf(" %[^\n]s", atual->nome);
      printf("Nova idade: ");
      scanf("%d", &atual->idade);
      printf("Novo RG: ");
      scanf(" %[^\n]s", atual->RG);
      printf("Novo dia de registro: ");
      scanf("%d", &atual->dia);
      printf("Novo mês de registro: ");
      scanf("%d", &atual->mes);
      printf("Novo ano de registro: ");
      scanf("%d", &atual->ano);

      printf("Dados atualizados com sucesso!\n");
      break;
    }
    atual = atual->prox;
  }

  if (!encontrado) {
    printf("Paciente não encontrado com o RG informado.\n");
  }
}

// Função para remover um paciente da lista com base no RG
void remover(){
  
  char rg_remover[15];
  printf("Digite o RG do paciente para remover o cadastro: ");
  scanf(" %[^\n]s", rg_remover);
  printf("\n");

  Paciente *atual = lista_pacientes;
  Paciente *anterior = NULL;
  int encontrado = 0;

  while (atual != NULL) {
    if (strcmp(atual->RG, rg_remover) == 0) {
      printf("Paciente encontrado:\n");
      printf("Nome: %s\n", atual->nome);
      printf("Idade: %d\n", atual->idade);
      printf("RG: %s\n", atual->RG);
      printf("Data de Registro: %d/%d/%d\n", atual->dia, atual->mes, atual->ano);
      encontrado = 1;

      char opcao;
      printf("\nTem certeza que deseja remover esse paciente? (S/N): ");
      scanf(" %c", &opcao);

      if (opcao == 'S' || opcao == 's') {
        if (anterior == NULL) {
          lista_pacientes = atual->prox;
        } 
        else {
          anterior->prox = atual->prox;
        }

        free(atual);
        printf("Cadastro do paciente removido com sucesso!\n");
      } 
      
      else {
        printf("Remoção cancelada.\n");
      }
      
    break;
    }
    
    anterior = atual;
    atual = atual->prox;
}

  if (!encontrado) {
    printf("Paciente não encontrado com o RG informado.\n");
  }
}

// Função principal de cadastro, apresenta um menu de opções e chama as funções correspondentes
int cadastro(){

  int opcao;

  printf("\n");
  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-= CADASTRO/CONSULTAS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
  printf("Seja Bem Vindo a parte de cadastros! Aqui está as funções de cadastro disnponiveis:\n\n");

  printf(".1) Cadastrar novo paciente\n");
  printf(".2) Consultar paciente cadastrado\n");
  printf(".3) Mostrar lista completa de pacientes\n");
  printf(".4) Atualizar dados de paciente\n");
  printf(".5) Remover paciente\n");
  printf(".6) Retornar ao menu principal\n\n");

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==\n\n");

  printf("Digite a opção desejada: ");
  scanf("%d", &opcao);
  printf("\n");

  if (opcao == 1){
    cadastro_novo();
    cadastro();
  }
  else if (opcao == 2){
    consultar();
    cadastro();
  }
  else if (opcao == 3){
    lista_de_pacientes();
    cadastro();
  }
  else if (opcao == 4){
    atualizar_dados();
    cadastro();
  }
  else if (opcao == 5){
    remover();
    cadastro();
  }
  else if (opcao == 6){
    printf("Voltando ao menu principal...\n\n");
  }
  else{
    printf("Opção invalida! Tente novamente.\n\n");
    cadastro();
  }

  return 0;

}

// Estrutura de nó para a fila de atendimento
typedef struct Node {
    Paciente *paciente; // Ponteiro para o paciente na fila
    struct Node *prox; // Ponteiro para o próximo nó na fila
} Node;

// Estrutura para a fila de atendimento
typedef struct {
    Node *inicio; // Ponteiro para o início da fila
    Node *fim; // Ponteiro para o fim da fila
} FilaAtendimento;

FilaAtendimento fila_atendimento; // Inicialização da fila de atendimento

// Função para enfileirar um paciente na fila de atendimento
void enfileirar(){
  
  char rg_enfileirar[15];
  printf("Digite o RG do paciente para enfileirar para atendimento: ");
  scanf(" %[^\n]s", rg_enfileirar);
  printf("\n");

  Paciente *paciente_enfileirado = NULL;
  Paciente *atual = lista_pacientes;
  int encontrado = 0;

  // Busca o paciente na lista de pacientes
  while (atual != NULL) {
    if (strcmp(atual->RG, rg_enfileirar) == 0) {
      paciente_enfileirado = atual;
      encontrado = 1;
      break;
    }
    atual = atual->prox;
  }

  if (encontrado) {
    Node *novo_no = (Node *)malloc(sizeof(Node));
    if (novo_no == NULL) {
      printf("Erro ao alocar memória para a fila.\n");
      return;
    }

    novo_no->paciente = paciente_enfileirado;
    novo_no->prox = NULL;

    if (fila_atendimento.fim == NULL) {
      fila_atendimento.inicio = novo_no;
    } 
      
    else {
      fila_atendimento.fim->prox = novo_no;
    }

    fila_atendimento.fim = novo_no;

    printf("Paciente enfileirado para atendimento com sucesso!\n");
  }
  
  else {
    printf("Paciente não encontrado com o RG informado.\n");
  }
}

// Função para desenfileirar um paciente da fila de atendimento
void desenfileirar(){

  if (fila_atendimento.inicio == NULL) {
    printf("Fila de atendimento vazia.\n");
    return;
  }

  Node *primeiro = fila_atendimento.inicio;

  printf("Paciente na frente da fila de atendimento:\n\n");
  printf("Nome: %s\n", primeiro->paciente->nome);
  printf("Idade: %d\n", primeiro->paciente->idade);
  printf("RG: %s\n", primeiro->paciente->RG);
  printf("Data de Registro: %d/%d/%d\n", primeiro->paciente->dia, primeiro->paciente->mes, primeiro->paciente->ano);

  char opcao;
  printf("\nTem certeza que deseja desenfileirar este paciente? (S/N): ");
  scanf(" %c", &opcao);
  printf("\n");

  if (opcao == 'S' || opcao == 's') {
    fila_atendimento.inicio = primeiro->prox;
    free(primeiro);
    printf("Paciente desenfileirado do atendimento com sucesso!\n");
  } 
  else {
    printf("Desenfileiramento cancelado.\n");
  }
}

// Função para mostrar os pacientes na fila de atendimento
void fila(){
  
  if (fila_atendimento.inicio == NULL) {
    printf("Fila de atendimento está vazia.\n");
    return;
  }

  Node *atual = fila_atendimento.inicio;
  printf("Pacientes na fila de atendimento:\n\n");

  while (atual != NULL) {
    printf("Nome: %s\n", atual->paciente->nome);
    printf("Idade: %d\n", atual->paciente->idade);
    printf("RG: %s\n", atual->paciente->RG);
    printf("Data de Registro: %d/%d/%d\n", atual->paciente->dia, atual->paciente->mes, atual->paciente->ano);
    printf("-------------------------\n");
    atual = atual->prox;
  }
}

// Função principal de atendimentos, apresenta um menu de opções e chama as funções correspondentes
int atendimentos(){

  int opcao;

  printf("\n");
  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-= ATENDIMENTOS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
  printf("Seja Bem Vindo a parte de atendimentos! Aqui estão a funções disponiveis:\n\n");

  printf(".1) Enfileirar\n");
  printf(".2) Desenfileirar paciente\n");
  printf(".3) Mostrar fila\n");
  printf(".4) Retornar ao menu principal\n\n");

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==\n\n");

  printf("Digite a opção desejada: ");
  scanf("%d", &opcao);
  printf("\n");

  if (opcao == 1){
    enfileirar();
    atendimentos();
  }
  else if (opcao == 2){
    desenfileirar();
    atendimentos();
  }
  else if (opcao == 3){
    fila();
    atendimentos();
  }
  else if (opcao == 4){
    printf("Voltando ao menu principal...\n\n");
  }
  else{
    printf("Opção invalida! Tente novamente.\n\n");
    atendimentos();
  }

  return 0;

}

// Estrutura para nós da Árvore Binária de Busca (ABB)
typedef struct NoABB {
  Paciente *paciente; // Armazena o paciente no nó da árvore
  struct NoABB *esquerda; // Nó filho à esquerda
  struct NoABB *direita; // Nó filho à direita
} NoABB;

NoABB *raiz = NULL; // Inicialização da árvore binária de busca

// Função para inserir um paciente em uma árvore binária de busca
NoABB *inserirABBByAno(NoABB *raiz, Paciente *novoPaciente) {
  if (raiz == NULL) {
    NoABB *novoNo = (NoABB *)malloc(sizeof(NoABB));
    if (novoNo == NULL) {
      printf("Erro ao alocar memória para a árvore.\n");
      return NULL;
    }
    novoNo->paciente = novoPaciente;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
  }

  if (novoPaciente->ano < raiz->paciente->ano) {
    raiz->esquerda = inserirABBByAno(raiz->esquerda, novoPaciente);
  } 
  else if (novoPaciente->ano > raiz->paciente->ano) {
    raiz->direita = inserirABBByAno(raiz->direita, novoPaciente);
  }
  
  return raiz;
  
}

// Função para criar uma árvore organizada por ano a partir da lista de pacientes
void listaParaABB() {
  Paciente *atual = lista_pacientes;
  while (atual != NULL) {
    raiz = inserirABBByAno(raiz, atual);
    atual = atual->prox;
  }
}

void registros_ano_ordenado(NoABB *raiz) {
  if (raiz != NULL) {
    registros_ano_ordenado(raiz->esquerda);

    printf("Nome: %s\n", raiz->paciente->nome);
    printf("Idade: %d\n", raiz->paciente->idade);
    printf("RG: %s\n", raiz->paciente->RG);
    printf("Data de Registro: %d/%d/%d\n", raiz->paciente->dia, raiz->paciente->mes, raiz->paciente->ano);
    printf("-------------------------\n");

    registros_ano_ordenado(raiz->direita);
  }
}

// Função para exibir todos os registros da árvore por ano
void registros_ano() {
    if (raiz == NULL) {
        printf("Árvore de registros vazia.\n");
        return;
    }

    printf("Todos os registros:\n\n");
    registros_ano_ordenado(raiz);
}

// Função para inserir um paciente na árvore binária de busca organizada por mês
NoABB *inserirABBByMes(NoABB *raiz, Paciente *novoPaciente) {
  if (raiz == NULL) {
    NoABB *novoNo = (NoABB *)malloc(sizeof(NoABB));
    if (novoNo == NULL) {
      printf("Erro ao alocar memória para a árvore.\n");
      return NULL;
    }

    novoNo->paciente = novoPaciente;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
  }

  if (novoPaciente->mes < raiz->paciente->mes) {
    raiz->esquerda = inserirABBByMes(raiz->esquerda, novoPaciente);
  } 

  else if (novoPaciente->mes > raiz->paciente->mes) {
    raiz->direita = inserirABBByMes(raiz->direita, novoPaciente);
  }

  return raiz;
}

// Função para criar uma árvore organizada por mes a partir da lista de pacientes
void listaParaABB2() {
  Paciente *atual = lista_pacientes;
  while (atual != NULL) {
    raiz = inserirABBByMes(raiz, atual);
    atual = atual->prox;
  }
}

// Função para exibir registros por mês na árvore
void registros_mes_ordenado(NoABB *raiz) {
  if (raiz != NULL) {
    registros_mes_ordenado(raiz->esquerda);

    printf("Nome: %s\n", raiz->paciente->nome);
    printf("Idade: %d\n", raiz->paciente->idade);
    printf("RG: %s\n", raiz->paciente->RG);
    printf("Data de Registro: %d/%d/%d\n", raiz->paciente->dia, raiz->paciente->mes, raiz->paciente->ano);
    printf("-------------------------\n");

    registros_mes_ordenado(raiz->direita);
  }
}

// Função para mostrar todos os registros na árvore
void registros_mes() {
  if (raiz == NULL) {
    printf("Árvore de registros vazia.\n");
    return;
  }

  printf("Todos os registros na árvore:\n\n");
  registros_mes_ordenado(raiz);
}

// Função para inserir um paciente na árvore binária de busca organizada por dia
NoABB *inserirABBByDia(NoABB *raiz, Paciente *novoPaciente) {
  if (raiz == NULL) {
    NoABB *novoNo = (NoABB *)malloc(sizeof(NoABB));
    if (novoNo == NULL) {
      printf("Erro ao alocar memória para a árvore.\n");
      return NULL;
    }
    novoNo->paciente = novoPaciente;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
  }

  if (novoPaciente->dia < raiz->paciente->dia) {
    raiz->esquerda = inserirABBByDia(raiz->esquerda, novoPaciente);
  } 
  else if (novoPaciente->dia > raiz->paciente->dia) {
    raiz->direita = inserirABBByDia(raiz->direita, novoPaciente);
  }
  
  return raiz;
}

// Função para criar uma árvore organizada por dia a partir da lista de pacientes
void listaParaABB3() {
  Paciente *atual = lista_pacientes;
  while (atual != NULL) {
    raiz = inserirABBByDia(raiz, atual);
    atual = atual->prox;
  }
}

// Função para exibir registros por dia na árvore
void registros_dia_ordenado(NoABB *raiz) {
  if (raiz != NULL) {
    registros_dia_ordenado(raiz->esquerda);

    printf("Nome: %s\n", raiz->paciente->nome);
    printf("Idade: %d\n", raiz->paciente->idade);
    printf("RG: %s\n", raiz->paciente->RG);
    printf("Data de Registro: %d/%d/%d\n", raiz->paciente->dia, raiz->paciente->mes, raiz->paciente->ano);
    printf("-------------------------\n");

    registros_dia_ordenado(raiz->direita);
  }
}

// Função para mostrar todos os registros na árvore
void registros_dia() {
  if (raiz == NULL) {
    printf("Árvore de registros vazia.\n");
    return;
  }

  printf("Todos os registros na árvore:\n\n");
  registros_dia_ordenado(raiz);
}

// Função para inserir um paciente na árvore binária de busca organizada por idade
NoABB *inserirABBByIdade(NoABB *raiz, Paciente *novoPaciente) {
  if (raiz == NULL) {
    NoABB *novoNo = (NoABB *)malloc(sizeof(NoABB));
    if (novoNo == NULL) {
      printf("Erro ao alocar memória para a árvore.\n");
      return NULL;
    }
    novoNo->paciente = novoPaciente;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
  }

  if (novoPaciente->idade < raiz->paciente->idade) {
    raiz->esquerda = inserirABBByIdade(raiz->esquerda, novoPaciente);
  } 
    
  else if (novoPaciente->idade > raiz->paciente->idade) {
    raiz->direita = inserirABBByIdade(raiz->direita, novoPaciente);
  }

  return raiz;
}

// Função para criar uma árvore organizada por idade a partir da lista de pacientes
void listaParaABB4() {
  Paciente *atual = lista_pacientes;
  while (atual != NULL) {
    raiz = inserirABBByIdade(raiz, atual);
    atual = atual->prox;
  }
}

// Função para exibir registros por idade na árvore
void registros_idade_ordenado(NoABB *raiz) {
  if (raiz != NULL) {
    registros_idade_ordenado(raiz->esquerda);

    printf("Nome: %s\n", raiz->paciente->nome);
    printf("Idade: %d\n", raiz->paciente->idade);
    printf("RG: %s\n", raiz->paciente->RG);
    printf("Data de Registro: %d/%d/%d\n", raiz->paciente->dia, raiz->paciente->mes, raiz->paciente->ano);
    printf("-------------------------\n");

    registros_idade_ordenado(raiz->direita);
  }
}

// Função para mostrar todos os registros na árvore
void registros_idade() {
  if (raiz == NULL) {
    printf("Árvore de registros vazia.\n");
    return;
  }

  printf("Todos os registros na árvore:\n\n");
  registros_idade_ordenado(raiz);
}


// Função para executar operações de pesquisa na árvore binária de busca
int pesquisa(){

  int opcao;

  printf("\n");
  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PESQUISA =-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
  printf("Seja Bem Vindo a parte de pesquisa! Aqui estão a funções disponiveis:\n\n");

  printf(".1) Mostrar registros ordenados por ano de registro\n");
  printf(".2) Mostrar registros ordenados por mês de registro\n");
  printf(".3) Mostrar registros ordenados por dia de registro\n");
  printf(".4) Mostrar registros ordenados por idade do paciente\n");
  printf(".5) Retornar ao menu principal\n\n");

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
  printf("Digite a opção desejada: ");
  scanf("%d", &opcao);
  printf("\n");

  if (opcao == 1){
    listaParaABB();
    registros_ano();
    pesquisa();
  }
  else if (opcao == 2){
    listaParaABB2();
    registros_mes();
    pesquisa();
  }
  else if (opcao == 3){
    listaParaABB3();
    registros_dia();
    pesquisa();
  }
  else if (opcao == 4){
    listaParaABB4();
    registros_idade();
    pesquisa();
  }
  else if (opcao == 5){
    printf("Voltando ao menu principal...\n\n");
  }
  else{
    printf("Opção invalida! Tente novamente.\n\n");
    pesquisa();
  }

  return 0;
  
}

// Função para criar um novo paciente e preencher seus detalhes
Paciente *criar_paciente(const char nome[], int idade, const char RG[], int dia, int mes, int ano) {
  
  // Aloca espaço para um novo paciente
  Paciente *novo_paciente = (Paciente *)malloc(sizeof(Paciente));

  // Preenche os detalhes do novo paciente com os parâmetros fornecidos
  if (novo_paciente != NULL) {
    strcpy(novo_paciente->nome, nome);
    novo_paciente->idade = idade;
    strcpy(novo_paciente->RG, RG);
    novo_paciente->dia = dia;
    novo_paciente->mes = mes;
    novo_paciente->ano = ano;
    novo_paciente->prox = NULL;
  } 
    
  else {
    printf("Erro ao alocar memória para o novo paciente.\n");
  }

  return novo_paciente;
  
}

// Função para inserir um novo paciente no início da lista de pacientes, evitando duplicações
void inserir_paciente(Paciente **lista, Paciente *novo_paciente) {
  Paciente *atual = *lista;
  
  while (atual != NULL) {
    // Verifica se o paciente já existe na lista (comparando pelo RG)
    if (strcmp(atual->RG, novo_paciente->RG) == 0) {
      free(novo_paciente); // Libera a memória alocada para o paciente repetido
      return;
    }
    atual = atual->prox;
  }

  if (*lista == NULL) {
    // Se a lista estiver vazia, o novo paciente se torna o primeiro da lista
    *lista = novo_paciente;
  } else {
    // Se a lista já contém elementos, o novo paciente é inserido no início
    novo_paciente->prox = *lista;
    *lista = novo_paciente;
  }
  
}

// Função para ler dados de pacientes de um arquivo e carregar na lista de pacientes
void ler_arquivo(){
  
  FILE *arquivo;
  arquivo = fopen("dados_pacientes_salvos.txt", "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  // Lê os dados do arquivo para criar um novo paciente
  while (!feof(arquivo)) {
    char nome[50];
    int idade, dia, mes, ano;
    char rg[15];

    fscanf(arquivo, "%s %d %s %d %d %d", nome, &idade, rg, &dia, &mes, &ano);

    // Criar um novo paciente com os dados lidos do arquivo
    Paciente *novo_paciente = criar_paciente(nome, idade, rg, dia, mes, ano);

    // Inserir o novo_paciente na lista
    inserir_paciente(&lista_pacientes, novo_paciente);
    
  }

  fclose(arquivo);

  printf("Arquivo carregado\n");
}

// Função para salvar os dados dos pacientes em um arquivo
void salvar_arquivo(Paciente *lista){
  
  FILE *arquivo;
  arquivo = fopen("dados_pacientes_salvos.txt", "w");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para salvar os dados dos pacientes.\n");
    return;
  }

  Paciente *atual = lista;

  // Escreve os dados dos pacientes no arquivo
  while (atual != NULL) {
    fprintf(arquivo, "%s %d %s %d %d %d\n", atual->nome, atual->idade, atual->RG, atual->dia, atual->mes, atual->ano);
    atual = atual->prox;
  }

  fclose(arquivo);

  printf("Arquivo salvo\n");
  
}

// Função para oferecer opções de carregar/salvar dados dos pacientes
int carregar(){

  int opcao;

  printf("\n");
  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-= ARQUIVOS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
  printf("Seja Bem Vindo a parte de salvar/carregar! Aqui estão a funções disponiveis:\n\n");

  printf(".1) Ler um arquivo com os dados dos pacientes e carregar a lista\n");
  printf(".2) Salvar um arquivo com os dados dos pacientes\n");
  printf(".3) Retornar ao menu principal\n\n");

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==\n\n");
  
  printf("Digite a opção desejada: ");
  scanf("%d", &opcao);
  printf("\n");

  if (opcao == 1){
    ler_arquivo();
    carregar();
  }
  else if (opcao == 2){
    salvar_arquivo(lista_pacientes);
    carregar();
  }
  else if (opcao == 3){
    printf("Voltando ao menu principal...\n\n");
  }
  else{
    printf("Opção invalida! Tente novamente.\n\n");
    atendimentos();
  }
  
  return 0;
}

//Função que fornece as informações do grupo
void sobre(){

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-= GRUPO =-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
  
  printf("Aplicativo de Gerenciamento de Serviços de Saúde\n\n");
  printf("Projeto Estrutura de Dados\n\n");

  printf("Grupo: \n");
  printf("- Rafael Leal Silva -> RA: 22.122.029-6\n");
  printf("- Juan Caio Galera  -> RA: 22.122.067-6\n");
  printf("\n");
  printf("3º Ciclo - FEI - Ciencias da Computação - CC4652\n\n");

  printf("28.10.2023\n\n");

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

  return;

}

// Função que mostra o menu de opções para o usuario escolher que ação deseja tomar dentro do programa
int menu(){

  int escolha;

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

  printf("Bem Vindo, este é Menu Principal! Aqui estão as ações disponiveis: \n\n");

  printf("1 - Cadastros / Consultas\n");
  printf("2 - Atendimento\n");
  printf("3 - Pesquisa\n");
  printf("4 - Carregar / Salvar Arquivo(s)\n");
  printf("5 - Sobre nós!\n");
  printf("\n0 - Finaliza programa\n\n");

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
  printf("Por gentileza digite o numero do que deseja fazer: ");
  scanf("%d", &escolha);
  printf("\n");

  if(escolha == 1){
    cadastro();
    menu();
  }
  else if(escolha == 2){
    atendimentos();
    menu();
  }
  else if(escolha == 3){
    pesquisa();
    menu();
  }
  else if(escolha == 4){
    carregar();
    menu();
  }
  else if(escolha == 5){
    sobre();
    menu();
  }
  else if(escolha == 0){
    printf("Programa Finalizado!");
  }
  else{
    printf("Escolha invalida! Favor tentar novamente\n\n");
    menu();
  }

  return 0;
}

int main(void) {
  
  menu();
  return 0;
}

