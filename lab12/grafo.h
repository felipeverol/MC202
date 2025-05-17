#include "fila.h"

typedef struct grafo *p_grafo;

struct grafo {
    p_no *adjacencia;
    int n;
};

p_grafo criar_grafo(int n);
void libera_lista(p_no lista);
void destroi_grafo(p_grafo g);
p_no insere_na_lista(p_no lista, int v);
int tem_aresta(p_grafo g, int u, int v);
void insere_aresta(p_grafo g, int u, int v);
void remove_aresta(p_grafo g, int u, int v);
int busca_rec(p_grafo g, int *visitado , int v, int t);
int existe_caminho(p_grafo g, int s, int t);
int* busca_em_largura(p_grafo g, int s, int t);
void imprimir_caminho(int v, int *pai);