#include "exercicio2a.h"
#include <stdlib.h>

unsigned converter(string s) {
  unsigned h = 0;
  for (int i = 0; s[i] != '\0'; i++)
    h = h * 256 + s[i];
  return h;
}

// Definicao de funcoes para manipulacao do TAD lista
lista *cria_lista(unsigned tamanho) {
  lista *nova_lista = (lista *)malloc(sizeof(lista));
  nova_lista->elemento = (string *)malloc(sizeof(string) * tamanho);
  nova_lista->tamanho = tamanho;
  for (int i = 0; i < tamanho; i++) {
    nova_lista->elemento[i] = (string)malloc(sizeof(char) * MAX_STRING_LEN);
  }
  return nova_lista;
}

void destroi_lista(lista *lista_de_strings) {
  for (int i = 0; i < lista_de_strings->tamanho; i++) {
    free(lista_de_strings->elemento[i]);
  }
  free(lista_de_strings->elemento);
  free(lista_de_strings);
}

void ler_strings(const char *arquivo, lista *lista_strings) {
  FILE *f = fopen(arquivo, "r");

  for (int i = 0; !feof(f); i++) {
    fscanf(f, "%s\n", lista_strings->elemento[i]);
  }

  fclose(f);
}

unsigned h_div(unsigned x, unsigned i, unsigned B) { return ((x % B) + i) % B; }

unsigned h_mul(unsigned x, unsigned i, unsigned B) {
  const double A = 0.6180;
  return ((int)((fmod(x * A, 1) * B) + i)) % B;
}
