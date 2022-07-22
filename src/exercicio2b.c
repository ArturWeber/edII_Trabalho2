#include "exercicio2.h"
#include "tabelaHash2ab.h"

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
