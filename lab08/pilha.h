/* Define struct do nó da pilha */
typedef struct noP* p_noP;
struct noP{
    char valor;
    p_noP prox;
};

/* Define struct da pilha */
typedef struct pilha* p_pilha;
struct pilha{
    int tam;
    p_noP topo;
};

p_pilha criaPilha();
void empilha(p_pilha p, char valor);
char desempilha(p_pilha p);
