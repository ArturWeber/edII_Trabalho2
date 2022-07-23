// Exercicio2b para o segundo projeito de SCC 0224/0606 – Estruturas de Dados II
// Alunos:
// 	Artur Brenner Weber - NUSP 12675451
//	Carlos Henrique Craveiro Aquino Veras - NUSP 12547187
// 	Pedro Borges Gudin - NUSP 12547997

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // funções strcmp e strcpy
#include <time.h>

/* Funcoes para medicao de Tempo*/
clock_t _ini, _fim;

void inicia_tempo() {
  srand(time(NULL));
  _ini = clock();
}

double finaliza_tempo() {
  _fim = clock();
  return ((double)(_fim - _ini)) / CLOCKS_PER_SEC;
}
/* Fim das funcoes para medicao de tempo */

/* Funcoes presentes em todos os exercicios da parte 2 */

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

// Definição do tipo string
typedef char *string;
#define MAX_STRING_LEN 20

// Definicao do tipo lista
typedef struct {
  string *elemento;
  unsigned tamanho;
} lista;

unsigned converter(string s) {
  unsigned h = 0;
  for (int i = 0; s[i] != '\0'; i++)
    h = h * 256 + s[i];
  return h;
}

// Definicao de funcoes para manipulacao do TAD lista
lista *cria_lista(unsigned tamanho) {
  lista *nova_lista = (lista *)malloc(sizeof(lista));
  nova_lista->elemento = (string *)malloc(sizeof(string) * tamanho);
  nova_lista->tamanho = tamanho;
  for (int i = 0; i < tamanho; i++) {
    nova_lista->elemento[i] = (string)malloc(sizeof(char) * MAX_STRING_LEN);
  }
  return nova_lista;
}

void destroi_lista(lista *lista_de_strings) {
  for (int i = 0; i < lista_de_strings->tamanho; i++) {
    free(lista_de_strings->elemento[i]);
  }
  free(lista_de_strings->elemento);
  free(lista_de_strings);
}

void ler_strings(const char *arquivo, lista *lista_strings) {
  FILE *f = fopen(arquivo, "r");

  for (int i = 0; !feof(f); i++) {
    fscanf(f, "%s\n", lista_strings->elemento[i]);
  }

  fclose(f);
}
/*Fim das funcoes presentes em todos os exercicios da parte 2*/

/* Funcoes Hash*/
unsigned h_div(unsigned x, unsigned i, unsigned B) { return ((x % B) + i) % B; }

unsigned h_mul(unsigned x, unsigned i, unsigned B) {
  const double A = 0.6180;
  return ((int)((fmod(x * A, 1) * B) + i)) % B;
}

unsigned h_dup(unsigned x, unsigned i, unsigned B) {
  return ((int)(h_mul(x, 0, B) + i * h_div(x, 0, B))) % B;
}
/* Fim das Funcoes Hash */

/* Inicio do TAD de Tabela Hash */
typedef struct {
  string *hash;
  unsigned tamanho;
} tabela_hash;

tabela_hash *cria_tabela(unsigned tamanho_tabela) {
  tabela_hash *tabela = (tabela_hash *)malloc(sizeof(tabela_hash));
  tabela->hash = (string *)malloc(sizeof(string) * tamanho_tabela);
  tabela->tamanho = tamanho_tabela;

  for (int i = 0; i < tamanho_tabela; i++) {
    tabela->hash[i] = malloc(MAX_STRING_LEN * sizeof(char));
    tabela->hash[i][0] = '\0';
  }

  return tabela;
}

unsigned insere_na_tabela(tabela_hash *tabela, lista *insercoes,
                          unsigned (*func_hash)(unsigned, unsigned, unsigned)) {
  unsigned int colisoes = 0;
  // insere as palavras da lista de insercoes na tabela hash
  for (int i = 0; i < insercoes->tamanho; i++) {
    bool insucesso = 1;
    unsigned tentativas = 0;
    while (insucesso) {
      unsigned int endereco = (*func_hash)(converter(insercoes->elemento[i]),
                                           tentativas, tabela->tamanho);
      if (tabela->hash[endereco][0] ==
          '\0') { // SE A POSICAO ESTIVER DESOCUPADA
        strcpy(tabela->hash[endereco],
               insercoes->elemento[i]); // INSIRA A PALAVRA NAQUELA POSICAO
        insucesso = FALSE;              // QUEBRA DE LOOP
      } else {
        tentativas++; // CASO CONTRARIO TENTE NOVAMENTE NA PROXIMA POSICAO
      }
    }
    if (tentativas > 0) { // POR FIM, CASO TENHA HAVIDO COLISOES NESSA TENTATIVA
                          // DE INSERCAO, CONTABILIZE-A
      colisoes++;
    }
  }
  return colisoes;
}

unsigned consulta_na_tabela(tabela_hash *tabela, lista *consultas,
                            unsigned (*func_hash)(unsigned, unsigned,
                                                  unsigned)) {
  unsigned int encontrados = 0;
  for (int i = 0; i < consultas->tamanho; i++) {
    bool insucesso = TRUE;
    unsigned int tentativas = 0;
    while (insucesso) {
      unsigned int endereco = (*func_hash)(converter(consultas->elemento[i]),
                                           tentativas, tabela->tamanho);
      if (strcmp(tabela->hash[endereco], consultas->elemento[i]) ==
          0) { // SE CONSULTA == PALAVRA NA POSICAO "HASH" DA TABELA, ENTAO
        encontrados++;     // A PALAVRA FOI ENCONTRADA
        insucesso = FALSE; // QUEBRA DE LOOP

      } else if (tabela->hash[endereco][0] !=
                 '\0') { // CASO A PALAVRA NAO SEJA IGUAL A DESEJADA, POREM A
                         // POSICAO ESTIVER OCUPADA, PROCURE NA PROXIMA
        tentativas++;    // PROXIMA TENTATIVA
      } else { // CASO A POSICAO ESTEJA VAZIA, ENTAO A PALAVRA NAO SE ENCONTRA
               // NA LISTA
        insucesso = FALSE; // QUEBRA DE LOOP
      }
    }
    // buscar consultas[i] na tabela hash
  }
  return encontrados;
}

void limpa_tabela(tabela_hash *tabela) {
  for (int i = 0; i < tabela->tamanho; i++) {
    tabela->hash[i][0] = '\0';
  }
}

void destroi_tabela(tabela_hash *tabela) {
  for (int i = 0; i < tabela->tamanho; i++) {
    free(tabela->hash[i]);
  }

  free(tabela->hash);
  free(tabela);
}
/* Fim do TAD de Tabela Hash */

int main(int argc, char const *argv[]) {
  const int N = 50000;
  const int M = 70000;
  const int B = 150001;

  unsigned colisoes = 0;
  unsigned encontrados = 0;

  lista *insercoes = cria_lista(N);
  lista *consultas = cria_lista(M);

  ler_strings("files/strings_entrada.txt", insercoes);
  ler_strings("files/strings_busca.txt", consultas);

  // cria tabela hash com hash por hash duplo
  tabela_hash *tabela = cria_tabela(B);

  // inserção dos dados na tabela hash
  inicia_tempo();

  colisoes = insere_na_tabela(tabela, insercoes, &h_dup);
  double tempo_insercao = finaliza_tempo();

  // busca dos dados na tabela hash
  inicia_tempo();

  encontrados = consulta_na_tabela(tabela, consultas, &h_dup);
  double tempo_busca = finaliza_tempo();

  // Libera memoria alocada para tabela
  destroi_tabela(tabela);

  //   Libera memoria alocada para as listas de insercao e consulta
  destroi_lista(insercoes);
  destroi_lista(consultas);

  printf("Colisões na inserção: %d\n", colisoes);
  printf("Tempo de inserção   : %fs\n", tempo_insercao);
  printf("Tempo de busca      : %fs\n", tempo_busca);
  printf("Itens encontrados   : %d\n", encontrados);

  return 0;
}
