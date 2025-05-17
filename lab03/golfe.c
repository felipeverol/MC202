#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

int main(){
    int n_partidas;
    struct partida *p;
    
    /* Chama as funções de partida.c e inicia o programa */
    scanf("%d ", &n_partidas);
    struct partida *partidas = malloc(n_partidas * sizeof(struct partida));
    for(int i = 0; i < n_partidas; i++){
        p = le_partida(i + 1);
        partidas[i] = *p;
        /* Limpa ponteiro auxiliar */
        free(p);
   } 
    for(int i = 0; i < n_partidas; i++)  
        imprime_partida(partidas + i);

    /* Livra o restante memória */
    for(int i = 0; i < n_partidas; i++)
        for(int j = 0; j < partidas[i].n_circuitos; j++)
            free(partidas[i].circuitos[j].n_jogadas);
    for(int i = 0; i < n_partidas; i++)
        free(partidas[i].circuitos);
    free(partidas);

    return 0;
}