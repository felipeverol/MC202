#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

#define PAI(i) ((i-1)/2) // Pai
#define F_ESQ(i) (2*i+1) // Filho esquerdo
#define F_DIR(i) (2*i+2) // Filho direito


/* Cria uma fila prioritária */
p_fp criaFilaPrio(int tam){
    p_fp fprio = malloc(sizeof(FP));
    fprio->v = malloc(tam * sizeof(Sobrevivente));
    fprio->n = 0;
    fprio->tam = tam;
    return fprio;
}

/* Troca valores de pointeiros de sobrevivente */
void troca(Sobrevivente* a, Sobrevivente* b){
    Sobrevivente t = *a;
    *a = *b;
    *b = t;
}

/* Função usada para reajustar o heap quando há um elemento 
   com mais prioridade que seu pai. Dessa forma, suas prioridades
   são comparadas e o filho troca com o pai */
void sobeHeap(p_fp fila, int k){
    if(k > 0 && fila->v[PAI(k)].nDiasSobrevividosAtual < fila->v[k].nDiasSobrevividosAtual){
        troca(&fila->v[k], &fila->v[PAI(k)]);
        sobeHeap(fila, PAI(k));
    }
}

/* Função usada para reajustar o heap quando há um elemento 
   com menos prioridade que seu maior filho. Dessa forma, suas prioridades
   são comparadas e o maior filho troca com o pai */
void desceHeap(p_fp fila, int k){
    int maior_filho;
    if(F_ESQ(k) < fila->n){
        maior_filho = F_ESQ(k);
        if(F_DIR(k) < fila->n && fila->v[F_ESQ(k)].nDiasSobrevividosAtual < fila->v[F_DIR(k)].nDiasSobrevividosAtual)
            maior_filho = F_DIR(k);
        if(fila->v[k].nDiasSobrevividosAtual < fila->v[maior_filho].nDiasSobrevividosAtual){
            troca(&fila->v[k], &fila->v[maior_filho]);
            desceHeap(fila, maior_filho);
        }
        
    }
}

/* Insere um novo sobrevivente no heap */
void insere(p_fp fila, Sobrevivente sobrevivente){
    fila->v[fila->n] = sobrevivente;
    fila->n++;
    sobeHeap(fila, fila->n - 1);
}

/* Retorna o sobrevivente com maior prioridade
   e o coloca no final da fila */
Sobrevivente extraiMax(p_fp fila){
    Sobrevivente sobrevivente = fila->v[0];
    troca(&fila->v[0], &fila->v[fila->n - 1]);
    fila->n--;
    desceHeap(fila, 0);
    return sobrevivente;
}

/* Altera a prioridade de algum sobrevivente e reajusta o heap */
void mudaPrioridade(p_fp fila, int k, int aumentoDias){
    if(aumentoDias > fila->v[k].nDiasSobrevividosAtual){
        fila->v[k].nDiasSobrevividosAtual = aumentoDias;
        sobeHeap(fila, k);
    } else {
        fila->v[k].nDiasSobrevividosAtual = aumentoDias;
        desceHeap(fila, k);
    }
}
