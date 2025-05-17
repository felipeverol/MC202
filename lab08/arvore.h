#include "pilha.h"

/* Define struct do nó da árvore */
typedef struct no* p_no;
struct no{
    char dado;
    p_no esq, dir;
};

bool operador(char c);
p_no criaArvore(p_pilha p);
void printaInordem(p_no raiz);
bool verifica(p_no raiz);
void reduz(p_no raiz);
void liberaAB(p_no raiz);
bool retornaReduziu();
void alteraReduziu(bool valor);