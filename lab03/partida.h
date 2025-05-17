#include "circuito.h"

struct partida{
    float aluguel;
    int id_partida;
    int n_participantes;
    int n_circuitos;
    int n_equipamentos;
    struct circuito *circuitos;
};

struct partida *le_partida(int id);
void imprime_partida(struct partida *partida);
int achar_mais_dificil(struct partida *partida);