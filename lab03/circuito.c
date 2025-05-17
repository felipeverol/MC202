#include <stdio.h>
#include <stdlib.h>
#include "circuito.h"

struct circuito *le_circuito(int n_participantes){
    struct circuito *circuito = malloc(sizeof(struct circuito));
    
    /* Lê variáveis da struct circuito */
    circuito->n_participantes = n_participantes;
    scanf("%d ", &circuito->id_circuito);
    circuito->n_jogadas = malloc(circuito->n_participantes * sizeof(int));
    
    for(int i = 0; i < circuito->n_participantes; i++)
        scanf("%d", &circuito->n_jogadas[i]);
    /* Retorna o ponteiro circuito */
    return circuito;
}