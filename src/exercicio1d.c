#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//PARA TESTE E DEBUGGING
void imprime_vetor(int* vetor, int primeiros){
  for (int i = 0; i < primeiros; i++){
    printf("%d\n", vetor[i]);
  }
}
void verifica_erro_vetor(int *consultas, int tamanho) {
  for (int i = 1; i < tamanho; i++){
    if (consultas[i] < consultas[i - 1]){
      printf("esse array aqui ta cagado seu idiota\n");
      return;
    }
  }
  printf("q bom q finalmente fez uma coisa util da tua vida! panaca\n");
}


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

int particao(int *consultas, int inicio, int fim) {
  int i = inicio;
  int j = fim;
  int p = (inicio + fim)/2;
  int pivot = consultas[p];
  while (i < j){
    while (pivot > consultas[i]) {
      i++;
    }
    while (pivot < consultas[j]) {
      j--;
    }
    if (i < j) {
      trocar(consultas, i, j);
    }
  }
  return j;
}

void quick_sort(int *consultas, int inicio, int fim) {
  if (inicio >= fim) {
    return;
  }
  int p = particao(consultas, inicio, fim); 
  quick_sort(consultas, inicio, p - 1);
  quick_sort(consultas, p + 1, fim);
}

int main(int argc, char const *argv[]) {
  const int N = 50000;
  const int index_size = 10000;
  unsigned encontrados = 0;

  int *entradas = ler_inteiros("files/inteiros_entrada.txt", N);
  int *consultas = ler_inteiros("files/inteiros_busca.txt", N);

  int *exemplo = ler_inteiros("files/inteiros_exemplo.txt", 11);

  // ordenar entrada
  verifica_erro_vetor(exemplo, 11);
  quick_sort(exemplo, 0, 10);
  verifica_erro_vetor(exemplo, 11);

  // criar tabela de indice


  // realizar consultas na tabela de indices
  inicia_tempo();
  for (int i = 0; i < N; i++) {
    // buscar o elemento consultas[i] na entrada
  }
  double tempo_busca = finaliza_tempo();

  printf("Tempo de busca    :\t%fs\n", tempo_busca);
  printf("Itens encontrados :\t%d\n", encontrados);

  free(entradas);
  free(consultas);

  return 0;
}
