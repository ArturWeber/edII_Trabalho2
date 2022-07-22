#include "listaEncadeada.h"

lista_encadeada_t *cria_lista_encadeada() {
  lista_encadeada_t *nova_lista =
      (lista_encadeada_t *)malloc(sizeof(lista_encadeada_t));
  nova_lista->fim = NULL;
  nova_lista->inicio = NULL;
  nova_lista->tamanho = 0;
  return nova_lista;
}

nodo_t *cria_nodo(string dado) {
  nodo_t *novo_nodo = (nodo_t *)malloc(sizeof(nodo_t));
  novo_nodo->dado = malloc(MAX_STRING_LEN * sizeof(char));
  strcpy(novo_nodo->dado, dado);
  novo_nodo->prox = NULL;
  return novo_nodo;
}

void destroi_nodo(nodo_t *nodo) {
  if (nodo == NULL) {
    return;
  }

  destroi_nodo(nodo->prox);
  free(nodo->dado);
  free(nodo);
}

void destroi_lista_encadeada(lista_encadeada_t *lista_enc) {
  destroi_nodo(lista_enc->inicio);
  free(lista_enc);
}
void insere_fim_lista_encadeada(lista_encadeada_t *lista_enc, string palavra) {
  if (lista_enc->tamanho == 0) {
    lista_enc->inicio = cria_nodo(palavra);
    lista_enc->fim = lista_enc->inicio;
    lista_enc->tamanho++;
    return;
  }

  lista_enc->fim->prox = cria_nodo(palavra);
  lista_enc->fim = lista_enc->fim->prox;
  lista_enc->tamanho++;
}
