#pragma once
#include "exercicio2.h"
#include "listaEncadeada.h"
// Definicao do tipo tabela_hash
typedef struct {
  lista_encadeada_t **hash;
  unsigned tamanho;
} tabela_hash_t;

tabela_hash_t *cria_tabela(unsigned tamanho_tabela);

unsigned insere_na_tabela(tabela_hash_t *tabela, lista *insercoes,
                          unsigned (*func_hash)(unsigned, unsigned, unsigned));

unsigned consulta_na_tabela(tabela_hash_t *tabela, lista *consultas,
                            unsigned (*func_hash)(unsigned, unsigned,
                                                  unsigned));
void limpa_tabela(tabela_hash_t *tabela);
void destroi_tabela(tabela_hash_t *tabela);
