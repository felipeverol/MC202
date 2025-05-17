typedef struct fila *p_fila;

typedef struct no *p_no;

struct no {
    int v;
    p_no prox;
};

struct fila {
    p_no ini, fim;
};

p_fila criar_fila();
void destruir_fila(p_fila f);
void enfileira(p_fila f, int x);
int desenfileira(p_fila f);