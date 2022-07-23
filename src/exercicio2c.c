// Exercicio2c para o segundo projeito de SCC 0224/0606 – Estruturas de Dados II
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
/* Fim das Funcoes Hash */

/* TAD de Lista Encadeada */
typedef struct nodo_t nodo_t;

struct nodo_t {
  string dado;
  nodo_t *prox;
};

typedef struct {
  unsigned tamanho;
  nodo_t *inicio;
  nodo_t *fim;
} lista_encadeada_t;

lista_encadeada_t *cria_lista_encadeada() {
  lista_encadeada_t *nova_lista =
      (lista_encadeada_t *)malloc(sizeof(lista_encadeada_t));
  nova_lista->fim = NULL;
  nova_lista->inicio = NULL;
  nova_lista->tamanho = 0;
  return nova_lista;
}

nodo_t *cria_nodo(string dado) {
  nodo_t *novo_nodo = (nodo_t *)malloc(sizeof(nodo_t));
  novo_nodo->dado = malloc(MAX_STRING_LEN * sizeof(char));
  strcpy(novo_nodo->dado, dado);
  novo_nodo->prox = NULL;
  return novo_nodo;
}

void destroi_nodo(nodo_t *nodo) {
  if (nodo == NULL) {
    return;
  }

  destroi_nodo(nodo->prox);
  free(nodo->dado);
  free(nodo);
}

void destroi_lista_encadeada(lista_encadeada_t *lista_enc) {
  destroi_nodo(lista_enc->inicio);
  free(lista_enc);
}
void insere_fim_lista_encadeada(lista_encadeada_t *lista_enc, string palavra) {
  if (lista_enc->tamanho == 0) {
    lista_enc->inicio = cria_nodo(palavra);
    lista_enc->fim = lista_enc->inicio;
    lista_enc->tamanho++;
    return;
  }

  lista_enc->fim->prox = cria_nodo(palavra);
  lista_enc->fim = lista_enc->fim->prox;
  lista_enc->tamanho++;
}
/* Fim do TAD de Lista Encadeada */

/* Inicio do TAD da Tabela Hash*/
// Definicao do tipo tabela_hash
typedef struct {
  lista_encadeada_t **hash;
  unsigned tamanho;
} tabela_hash_t;

tabela_hash_t *cria_tabela(unsigned tamanho_tabela) {
  tabela_hash_t *nova_tabela_hash =
      (tabela_hash_t *)malloc(sizeof(tabela_hash_t));
  nova_tabela_hash->hash = (lista_encadeada_t **)malloc(
      sizeof(lista_encadeada_t *) * tamanho_tabela);
  nova_tabela_hash->tamanho = tamanho_tabela;
  for (int i = 0; i < tamanho_tabela; i++) {
    nova_tabela_hash->hash[i] = cria_lista_encadeada();
  }
  return nova_tabela_hash;
}

unsigned insere_na_tabela(tabela_hash_t *tabela, lista *insercoes,
                          unsigned (*func_hash)(unsigned, unsigned, unsigned)) {
  unsigned int colisoes = 0;
  // insere as palavras da lista de insercoes na tabela hash
  for (int i = 0; i < insercoes->tamanho; i++) {
    unsigned int endereco =
        (*func_hash)(converter(insercoes->elemento[i]), 0, tabela->tamanho);
    if (tabela->hash[endereco]->tamanho != 0) { // DE INSERCAO, CONTABILIZE-A
      colisoes++;
    }
    insere_fim_lista_encadeada(
        tabela->hash[endereco],
        insercoes->elemento[i]); // INSIRA A PALAVRA NAQUELA POSICAO
  }

  return colisoes;
}

unsigned consulta_na_tabela(tabela_hash_t *tabela, lista *consultas,
                            unsigned (*func_hash)(unsigned, unsigned,
                                                  unsigned)) {
  unsigned int encontrados = 0;
  for (int i = 0; i < consultas->tamanho; i++) {
    unsigned int endereco =
        (*func_hash)(converter(consultas->elemento[i]), 0, tabela->tamanho);
    nodo_t *nodo_atual = tabela->hash[endereco]->inicio;
    while (nodo_atual != NULL) {
      if (strcmp(nodo_atual->dado, consultas->elemento[i]) ==
          0) { // SE CONSULTA == PALAVRA NA POSICAO "HASH" DA TABELA, ENTAO
        encontrados++; // A PALAVRA FOI ENCONTRADA
        break;         // QUEBRA DE LOOP
      }
      // CASO CONTRARIO, PROCURAR NO PROXIMO ELEMENTO DA LISTA
      nodo_atual = nodo_atual->prox;
    }
  }
  return encontrados;
}

void limpa_tabela(tabela_hash_t *tabela) {
  for (int i = 0; i < tabela->tamanho; i++) {
    destroi_lista_encadeada(tabela->hash[i]);
    tabela->hash[i] = cria_lista_encadeada();
  }
}

void destroi_tabela(tabela_hash_t *tabela) {
  for (int i = 0; i < tabela->tamanho; i++) {
    destroi_lista_encadeada(tabela->hash[i]);
  }
  free(tabela->hash);
  free(tabela);
}
/* Fim do TAD de Tabela Hash*/

int main(int argc, char const *argv[]) {
  const int N = 50000;
  const int M = 70000;
  const int B = 150001;

  unsigned colisoes_h_div = 0;
  unsigned colisoes_h_mul = 0;

  unsigned encontrados_h_div = 0;
  unsigned encontrados_h_mul = 0;

  lista *insercoes = cria_lista(N);
  lista *consultas = cria_lista(M);

  ler_strings("files/strings_entrada.txt", insercoes);
  ler_strings("files/strings_busca.txt", consultas);

  // cria tabela hash com hash por divisão
  tabela_hash_t *tabela = cria_tabela(B);

  // inserção dos dados na tabela hash com hash por divisão
  inicia_tempo();
  colisoes_h_div = insere_na_tabela(tabela, insercoes, &h_div);
  double tempo_insercao_h_div = finaliza_tempo();

  // busca dos dados na tabela hash com hash por divisão
  inicia_tempo();
  encontrados_h_div = consulta_na_tabela(tabela, consultas, &h_div);
  double tempo_busca_h_div = finaliza_tempo();

  // limpa tabela com hash por multiplicacao
  limpa_tabela(tabela);

  // inserção dos dados na tabela hash com hash por multiplicação
  inicia_tempo();
  colisoes_h_mul = insere_na_tabela(tabela, insercoes, &h_mul);
  double tempo_insercao_h_mul = finaliza_tempo();

  // busca dos dados na tabela hash com hash por multiplicação
  inicia_tempo();
  encontrados_h_mul = consulta_na_tabela(tabela, consultas, &h_mul);
  double tempo_busca_h_mul = finaliza_tempo();

  // destroi tabela hash com hash por multiplicação
  destroi_tabela(tabela);
  destroi_lista(insercoes);
  destroi_lista(consultas);

  printf("Hash por Divisão\n");
  printf("Colisões na inserção: %d\n", colisoes_h_div);
  printf("Tempo de inserção   : %fs\n", tempo_insercao_h_div);
  printf("Tempo de busca      : %fs\n", tempo_busca_h_div);
  printf("Itens encontrados   : %d\n", encontrados_h_div);
  printf("\n");
  printf("Hash por Multiplicação\n");
  printf("Colisões na inserção: %d\n", colisoes_h_mul);
  printf("Tempo de inserção   : %fs\n", tempo_insercao_h_mul);
  printf("Tempo de busca      : %fs\n", tempo_busca_h_mul);
  printf("Itens encontrados   : %d\n", encontrados_h_mul);

  return 0;
}
