#pragma once
#include "exercicio2.h"
#include <stdlib.h>

typedef struct nodo_t nodo_t;

struct nodo_t {
  string dado;
  nodo_t *prox;
};

typedef struct {
  unsigned tamanho;
  nodo_t *inicio;
  nodo_t *fim;
} lista_encadeada_t;

lista_encadeada_t *cria_lista_encadeada();
void destroi_lista_encadeada(lista_encadeada_t *lista_enc);
void insere_fim_lista_encadeada(lista_encadeada_t *lista_enc, string palavra);
nodo_t *cria_nodo(string dado);
void destroi_nodo(nodo_t *nodo);
