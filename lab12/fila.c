#include <stdlib.h>
#include "fila.h"

p_fila criar_fila() {
    p_fila f;
    f = malloc(sizeof(struct fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void destruir_fila(p_fila f) {
    while(f->ini != NULL)
        desenfileira(f);
    free(f);
}

void enfileira(p_fila f, int x) {
    p_no novo;
    novo = malloc(sizeof(struct no));
    novo->v = x;
    novo->prox = NULL;
    if (f->ini == NULL)
        f->ini = novo;
    else
        f->fim->prox = novo;
    f->fim = novo;
}

int desenfileira(p_fila f) {
    p_no primeiro = f->ini;
    int x = primeiro->v;
    f->ini = f->ini->prox;
    if (f->ini == NULL)
        f->fim = NULL;
    free(primeiro);
    return x;
}