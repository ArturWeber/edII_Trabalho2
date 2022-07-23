// Exercicio1a para o segundo projeito de SCC 0224/0606 – Estruturas de Dados II
// Alunos:
// 	Artur Brenner Weber - NUSP 12675451
//	Carlos Henrique Craveiro Aquino Veras - NUSP 12547187
// 	Pedro Borges Gudin - NUSP 12547997

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

// busca sequencial simples
void busca_sequencial_simples(int *entradas, int *consultas, int tamanhoEntrada,
                              int tamanhoConsulta, unsigned *encontrados) {
  //"for" duplo para percorrer os dois vetores completamente comparando                              
  for (int i = 0; i < tamanhoEntrada; i++) {
    for (int j = 0; j < tamanhoConsulta; j++) {
      if (entradas[i] == consultas[j]) {
        (*encontrados)++;
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  const int N = 50000;
  unsigned encontrados = 0;

  int *entradas = ler_inteiros("files/inteiros_entrada.txt", N);
  int *consultas = ler_inteiros("files/inteiros_busca.txt", N);

  // realiza busca sequencial
  inicia_tempo();
  busca_sequencial_simples(entradas, consultas, N, N, &encontrados);
  double tempo_busca = finaliza_tempo();

  printf("Tempo de busca    :\t%fs\n", tempo_busca);
  printf("Itens encontrados :\t%d\n", encontrados);

  free(entradas);
  free(consultas);

  return 0;
}