#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // funções strcmp e strcpy
#include <time.h>

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

// Definição do tipo string
typedef char *string;
#define MAX_STRING_LEN 20

// Headers para tratar do tipo string
unsigned converter(string s);
string *ler_strings(const char *arquivo, const int n);

// Funcoes para analise de tempo
void inicia_tempo();
double finaliza_tempo();

// Funcoes hash
unsigned h_div(unsigned x, unsigned i, unsigned B);
unsigned h_mul(unsigned x, unsigned i, unsigned B);
