#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // funções strcmp e strcpy

#include "funcs_time.h"

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

// Definição do tipo string
typedef char *string;
#define MAX_STRING_LEN 20

// Definicao do tipo lista
typedef struct {
  string *elemento;
  unsigned tamanho;
} lista;

// Declaracao de funcoes para manipulacao do TAD lista
lista *cria_lista(unsigned tamanho);
void destroi_lista(lista *lista_de_strings);

// Declaracao de funcoes para tratar do tipo string
unsigned converter(string s);

void ler_strings(const char *arquivo, lista *lista_strings);

// Declaracao das funcoes hash
unsigned h_div(unsigned x, unsigned i, unsigned B);
unsigned h_mul(unsigned x, unsigned i, unsigned B);
unsigned h_dup(unsigned x, unsigned i, unsigned B);
