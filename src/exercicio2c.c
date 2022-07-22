#include "exercicio2.h"

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

  // inserção dos dados na tabela hash com hash por divisão
  inicia_tempo();
  for (int i = 0; i < N; i++) {
    // inserir insercoes[i] na tabela hash
  }
  double tempo_insercao_h_div = finaliza_tempo();

  // busca dos dados na tabela hash com hash por divisão
  inicia_tempo();
  for (int i = 0; i < M; i++) {
    // buscar consultas[i] na tabela hash
  }
  double tempo_busca_h_div = finaliza_tempo();

  // destroi tabela hash com hash por divisão

  // cria tabela hash com hash por multiplicação

  // inserção dos dados na tabela hash com hash por multiplicação
  inicia_tempo();
  for (int i = 0; i < N; i++) {
    // inserir insercoes[i] na tabela hash
  }
  double tempo_insercao_h_mul = finaliza_tempo();

  // busca dos dados na tabela hash com hash por multiplicação
  inicia_tempo();
  for (int i = 0; i < M; i++) {
    // buscar consultas[i] na tabela hash
  }
  double tempo_busca_h_mul = finaliza_tempo();

  // destroi tabela hash com hash por multiplicação

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
