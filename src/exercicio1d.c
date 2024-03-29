// Exercicio1d para o segundo projeito de SCC 0224/0606 – Estruturas de Dados II
// Alunos:
// 	Artur Brenner Weber - NUSP 12675451
//	Carlos Henrique Craveiro Aquino Veras - NUSP 12547187
// 	Pedro Borges Gudin - NUSP 12547997

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
unsigned char typedef bool;
#define TRUE 1
#define FALSE 0

int *ler_inteiros(const char *arquivo, const int n) {
  FILE *f = fopen(arquivo, "r");

  int *inteiros = (int *)malloc(sizeof(int) * n);

  for (int i = 0; !feof(f); i++) {
    fscanf(f, "%d\n", &inteiros[i]);
  }

  fclose(f);

  return inteiros;
}

void inicia_tempo() {
  srand(time(NULL));
  _ini = clock();
}

double finaliza_tempo() {
  _fim = clock();
  return ((double)(_fim - _ini)) / CLOCKS_PER_SEC;
}

void trocar(int *consultas, int i, int j) {
  int aux = consultas[i];
  consultas[i] = consultas[j];
  consultas[j] = aux;
}

//algoritmo quick-sort de ordenacao 
void quick_sort(int *consultas, int inicio, int fim) {
  if (inicio >= fim) {
    return;
  }

  int i = inicio;
  int j = fim;
  int p = (inicio + fim) / 2;
  int pivot = consultas[p];

  while (i <= j) {
    while (pivot > consultas[i]) {
      i++;
    }
    while (pivot < consultas[j]) {
      j--;
    }
    if (i <= j) {
      trocar(consultas, i, j);
      i++;
      j--;
    }
  }

  quick_sort(consultas, inicio, j);
  quick_sort(consultas, i, fim);
}

//cria tabela de indice primario
int *cria_tabela_indice(int *consultas, int N, int index_size) {
  //usa ceil para quando index_size e numero nao multiplo de N
  int t = ceil((float)N / index_size);
  int *tabela = (int *)malloc(sizeof(int) * t);
  //atribui valores para a tabela de indice com base na tabela principal
  for (int i = 0; i < t; i++) {
    tabela[i] = consultas[index_size * i];
  }
  return tabela;
}

//funcao de busca
void busca_sequencial_tabelaindex(int *entradas, int *tabela, int *consultas,
                                  int tamanhoEntrada, int index_size,
                                  int tamanhoConsulta, unsigned *encontrados) {
  int tabelaIndice = ceil((float)tamanhoConsulta / index_size);
  for (int i = 0; i < tamanhoEntrada; i++) {
    int j = 0;
    //primeiro procura na tabela de indice primario
    while (entradas[i] > tabela[j + 1] &&
           (j + 1) < tabelaIndice) {
      j++;
    }
    //se nao encontrou na tabela de indice primario vai para proximo for
    if (j == tabelaIndice){
      break;
    } 
    //busca na tabela principal
    j *= index_size;
    while (entradas[i] >= consultas[j] && (j + 1) < tamanhoConsulta) {
      if (entradas[i] == consultas[j]) {
        (*encontrados)++;
      }
      j++;
    }
  }
}

int main(int argc, char const *argv[]) {
  const int N = 50000;
  const int index_size = 10000;
  unsigned encontrados = 0;

  int *entradas = ler_inteiros("files/inteiros_entrada.txt", N);
  int *consultas = ler_inteiros("files/inteiros_busca.txt", N);

  // ordenar entrada
  quick_sort(consultas, 0, N - 1);

  // criar tabela de indice
  int *tabela = cria_tabela_indice(consultas, N, index_size);

  // realizar busca
  inicia_tempo();
  busca_sequencial_tabelaindex(entradas, tabela, consultas, N, index_size, N,
                               &encontrados);
  double tempo_busca = finaliza_tempo();

  printf("Tempo de busca    :\t%fs\n", tempo_busca);
  printf("Itens encontrados :\t%d\n", encontrados);

  free(entradas);
  free(tabela);
  free(consultas);

  return 0;
}