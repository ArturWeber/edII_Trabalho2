#include "tabelaHash2c.h"
#include "listaEncadeada.h"

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
