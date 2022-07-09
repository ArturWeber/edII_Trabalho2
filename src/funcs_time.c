#include "funcs_time.h"

// Definição das variaveis GLOBAIS que controlam a medição de tempo
clock_t _ini, _fim;

void inicia_tempo() {
  srand(time(NULL));
  _ini = clock();
}

double finaliza_tempo() {
  _fim = clock();
  return ((double)(_fim - _ini)) / CLOCKS_PER_SEC;
}
