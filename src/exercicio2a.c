#include "exercicio2a.h"

int main(int argc, char const *argv[]) {
  unsigned N = 50000;
  unsigned M = 70000;
  unsigned B = 150001;

  unsigned colisoes_h_div = 0;
  unsigned colisoes_h_mul = 0;

  unsigned encontrados_h_div = 0;
  unsigned encontrados_h_mul = 0;

  string *insercoes = ler_strings("files/strings_entrada.txt", N);
  string *consultas = ler_strings("files/strings_busca.txt", M);

  // cria tabela hash com hash por divisão

  string *tabela_hash_div = (string *)malloc(sizeof(string) * B);
  for (int i = 0; i < B; i++) {
    tabela_hash_div[i] = malloc(MAX_STRING_LEN * sizeof(char));
    tabela_hash_div[i][0] = '\0';
  }

  // inserção dos dados na tabela hash usando hash por divisão
  inicia_tempo();
  int numerodeinsercoes = 0;
  for (int i = 0; i < N; i++) {
    int insucesso = 1;
    int tentativas = 0;
    while (insucesso) {
      unsigned int hash = h_div(converter(insercoes[i]), tentativas, B);
      if (tabela_hash_div[hash][0] == '\0') { // SE A POSICAO ESTIVER DESOCUPADA
        tabela_hash_div[hash] =
            insercoes[i];  // INSIRA A PALAVRA NAQUELA POSICAO
        insucesso = FALSE; // QUEBRA DE LOOP
        numerodeinsercoes++;
      } else {
        tentativas++; // CASO CONTRARIO TENTE NOVAMENTE NA PROXIMA POSICAO
      }
    }
    if (tentativas > 0) { // POR FIM, CASO TENHA HAVIDO COLISOES NESSA TENTATIVA
                          // DE INSERCAO, CONTABILIZE-A
      colisoes_h_div++;
    }
    // inserir insercoes[i] na tabela hash
  }
  double tempo_insercao_h_div = finaliza_tempo();

  // consulta dos dados na tabela hash usando hash por divisão
  int numeropesquisas = 0;
  inicia_tempo();
  for (int i = 0; i < M; i++) {
    int insucesso = 1;
    int tentativas = 0;
    while (insucesso) {
      unsigned int hash = h_div(converter(consultas[i]), tentativas, B);
      if (strcmp(tabela_hash_div[hash], consultas[i]) ==
          0) { // SE CONSULTA == PALAVRA NA POSICAO "HASH" DA TABELA, ENTAO
        encontrados_h_div++; // A PALAVRA FOI ENCONTRADA
        insucesso = FALSE;   // QUEBRA DE LOOP
        numeropesquisas++;
        // printf("%s == %s\n", tabela_hash_div[hash], consultas[i]);
      } else if (tabela_hash_div[hash][0] !=
                 '\0') { // CASO A PALAVRA NAO SEJA IGUAL A DESEJADA, POREM A
                         // POSICAO ESTIVER OCUPADA, PROCURE NA PROXIMA
        tentativas++;    // PROXIMA TENTATIVA
      } else { // CASO A POSICAO ESTEJA VAZIA, ENTAO A PALAVRA NAO SE ENCONTRA
               // NA LISTA
        insucesso = FALSE; // QUEBRA DE LOOP
        numeropesquisas++;
      }
    }
    // buscar consultas[i] na tabela hash
  }
  double tempo_busca_h_div = finaliza_tempo();

  // limpa a tabela hash com hash por divisão

  // cria tabela hash com hash por divisão
  string *tabela_hash_mul = (string *)malloc(sizeof(string) * B);
  for (int i = 0; i < B; i++) {
    tabela_hash_mul[i] = malloc(MAX_STRING_LEN * sizeof(char));
    tabela_hash_mul[i][0] = '\0';
  }
  // inserção dos dados na tabela hash usando hash por multiplicação
  inicia_tempo();

  numerodeinsercoes = 0;
  for (int i = 0; i < N; i++) {
    int insucesso = 1;
    int tentativas = 0;
    while (insucesso) {
      unsigned int hash = h_mul(converter(insercoes[i]), tentativas, B);
      if (tabela_hash_mul[hash][0] == '\0') { // SE A POSICAO ESTIVER DESOCUPADA
        tabela_hash_mul[hash] =
            insercoes[i];  // INSIRA A PALAVRA NAQUELA POSICAO
        insucesso = FALSE; // QUEBRA DE LOOP
        numerodeinsercoes++;
      } else {
        tentativas++; // CASO CONTRARIO TENTE NOVAMENTE NA PROXIMA POSICAO
      }
    }
    if (tentativas > 0) { // POR FIM, CASO TENHA HAVIDO COLISOES NESSA TENTATIVA
                          // DE INSERCAO, CONTABILIZE-A
      colisoes_h_mul++;
    }
    // inserir insercoes[i] na tabela hash
  }

  double tempo_insercao_h_mul = finaliza_tempo();

  // busca dos dados na tabela hash com hash por multiplicação
  inicia_tempo();

  numeropesquisas = 0;
  for (int i = 0; i < M; i++) {
    int insucesso = 1;
    int tentativas = 0;
    while (insucesso) {
      unsigned int hash = h_mul(converter(consultas[i]), tentativas, B);
      if (strcmp(tabela_hash_mul[hash], consultas[i]) ==
          0) { // SE CONSULTA == PALAVRA NA POSICAO "HASH" DA TABELA, ENTAO
        encontrados_h_mul++; // A PALAVRA FOI ENCONTRADA
        insucesso = FALSE;   // QUEBRA DE LOOP
        numeropesquisas++;
        // printf("%s == %s\n", tabela_hash_div[hash], consultas[i]);
      } else if (tabela_hash_mul[hash][0] !=
                 '\0') { // CASO A PALAVRA NAO SEJA IGUAL A DESEJADA, POREM A
                         // POSICAO ESTIVER OCUPADA, PROCURE NA PROXIMA
        tentativas++;    // PROXIMA TENTATIVA
      } else { // CASO A POSICAO ESTEJA VAZIA, ENTAO A PALAVRA NAO SE ENCONTRA
               // NA LISTA
        insucesso = FALSE; // QUEBRA DE LOOP
        numeropesquisas++;
      }
    }
    // buscar consultas[i] na tabela hash
  }

  double tempo_busca_h_mul = finaliza_tempo();

  // limpa a tabela hash com hash por multiplicação

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
