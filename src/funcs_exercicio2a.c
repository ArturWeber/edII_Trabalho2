#include "exercicio2a.h"

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

unsigned converter(string s) {
  unsigned h = 0;
  for (int i = 0; s[i] != '\0'; i++)
    h = h * 256 + s[i];
  return h;
}

string *ler_strings(const char *arquivo, const int n) {
  FILE *f = fopen(arquivo, "r");

  string *strings = (string *)malloc(sizeof(string) * n);

  for (int i = 0; !feof(f); i++) {
    strings[i] = (string)malloc(sizeof(char) * MAX_STRING_LEN);
    fscanf(f, "%s\n", strings[i]);
  }

  fclose(f);

  return strings;
}

void inicia_tempo() {
  srand(time(NULL));
  _ini = clock();
}

double finaliza_tempo() {
  _fim = clock();
  return ((double)(_fim - _ini)) / CLOCKS_PER_SEC;
}

unsigned h_div(unsigned x, unsigned i, unsigned B) { return ((x % B) + i) % B; }

unsigned h_mul(unsigned x, unsigned i, unsigned B) {
  const double A = 0.6180;
  return ((int)((fmod(x * A, 1) * B) + i)) % B;
}
