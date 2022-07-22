#pragma once
#include "exercicio2.h"
#include <stdlib.h>

// Definicao do tipo tabela_hash
typedef struct {
  string *hash;
  unsigned tamanho;
} tabela_hash;

tabela_hash *cria_tabela(unsigned tamanho_tabela);

unsigned insere_na_tabela(tabela_hash *tabela, lista *insercoes,
                          unsigned (*func_hash)(unsigned, unsigned, unsigned));

unsigned consulta_na_tabela(tabela_hash *tabela, lista *consultas,
                            unsigned (*func_hash)(unsigned, unsigned,
                                                  unsigned));
void limpa_tabela(tabela_hash *tabela);

void destroi_tabela(tabela_hash *tabela);
