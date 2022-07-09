#include "tabelaHash2a.h"
#include "exercicio2a.h"
#include <stdlib.h>

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
