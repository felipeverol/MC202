#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

p_grafo criar_grafo(int n) {
    p_grafo g = malloc(sizeof(struct grafo));
    g->n = n;
    g->adjacencia = malloc(n * sizeof(p_no));
    for(int i = 0; i < n; i++)
        g->adjacencia[i] = NULL;
    return g;
}

void libera_lista(p_no lista) {
    if(lista != NULL) {
        libera_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(p_grafo g) {
    for(int i = 0; i < g->n; i++)
        libera_lista(g->adjacencia[i]);
    free(g->adjacencia);
    free(g);
}

p_no insere_na_lista(p_no lista, int v) {
    p_no novo = malloc(sizeof(struct no));
    novo->v = v;
    novo->prox = lista;
    
    return novo;
}

int tem_aresta(p_grafo g, int u, int v) {
    if(g->adjacencia[u] != NULL)
        for(p_no t = g->adjacencia[u]; t != NULL; t = t->prox)
            if(t->v == v)
                return 1;
    return 0;
}

void insere_aresta(p_grafo g, int u, int v) {
    if(!tem_aresta(g, u, v)){    
        g->adjacencia[v] = insere_na_lista(g->adjacencia[v], u);
        g->adjacencia[u] = insere_na_lista(g->adjacencia[u], v);
    }
}

p_no remove_da_lista(p_no lista, int v) {
    p_no proximo;
    if(lista == NULL)
        return NULL;
    else if(lista->v == v) {
        proximo = lista->prox;
        free(lista);
        return proximo;
    } else {
        lista->prox = remove_da_lista(lista->prox, v);
        return lista;
    }
}

void remove_aresta(p_grafo g, int u, int v) {
    if(tem_aresta(g, u, v)){
        g->adjacencia[u] = remove_da_lista(g->adjacencia[u], v);
        g->adjacencia[v] = remove_da_lista(g->adjacencia[v], u);
    }
}

int busca_rec(p_grafo g, int *visitado , int v, int t) {
    int w;
    if(v == t)
        return 1; 
    visitado[v] = 1;
    for(w = 0; w < g->n; w++)
        if(tem_aresta(g, v, w) && !visitado[w])
            if(busca_rec(g, visitado, w, t))
                return 1;
    return 0;
}

int existe_caminho(p_grafo g, int s, int t) {
    int encontrou , i, *visitado = malloc(g->n * sizeof(int));
    for(i = 0; i < g->n; i++)
        visitado[i] = 0;
    encontrou = busca_rec(g, visitado, s, t);
    free(visitado);
    return encontrou;
}

int* busca_em_largura(p_grafo g, int s, int t) {
    int w, v;
    int *pai = malloc(g->n * sizeof(int));
    int *visitado = malloc(g->n * sizeof(int));
    p_fila f = criar_fila();
    
    for(v = 0; v < g->n; v++) {
        pai[v] = -1;
        visitado[v] = 0;
    }
    
    enfileira(f,s);
    pai[s] = s;
    visitado[s] = 1;
    
    while(f->ini != NULL) {
        v = desenfileira(f);
        for(w = 0; w < g->n; w++)
            if(tem_aresta(g, v, w) && !visitado[w]) {
                visitado[w] = 1;
                pai[w] = v;
                enfileira(f, w);
            
                if(w == t){
                    destruir_fila(f);
                    free(visitado);
                    return pai;
                }
            }
    }

    destruir_fila(f);
    free(visitado);
    free(pai);
    return NULL;
}

void imprimir_caminho(int v, int *pai) {
    if(pai[v] != v)
        imprimir_caminho(pai[v], pai);
    printf("%d ->", v);
}