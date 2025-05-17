#include <stdlib.h>
#include "pilha.h"

/* Aloca a pilha */
p_pilha criaPilha(){
    p_pilha p = malloc(sizeof(struct pilha));
    p->tam = 0;
    p->topo = NULL;
    return p;
}

/* Empilha elementos na pilha */
void empilha(p_pilha p, char valor){
    p_noP no = malloc(sizeof(struct noP));
    no->valor = valor;
    no->prox = p->topo;
    p->topo = no;
    p->tam++;
}

/* Desempilha, livra e retorna o elemento do topo */
char desempilha(p_pilha p){
    char c;
    p_noP topo = p->topo;
    if(p->tam > 1)
        p->topo = p->topo->prox;
    p->tam--;
    c = topo->valor;
    free(topo);
    return c;
}
