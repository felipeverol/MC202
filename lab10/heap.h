/* Define a struct de um sobrevivente */
typedef struct{
    char nome[32];
    char prato[25];
    int nDiasSobrevividos; // Prioridade "fixa" do sobrevivente
    int nDiasSobrevividosAtual; // Prioridade que se alterável, mas depois retorna a prioridade fixa
    int ID;
} Sobrevivente;

/* Define struct de uma fila prioritária */
typedef struct{
    Sobrevivente* v;
    int n, tam;
} FP;
typedef FP* p_fp;

p_fp criaFilaPrio(int tam);
void troca(Sobrevivente* a, Sobrevivente* b);
void sobeHeap(p_fp fila, int k);
void desceHeap(p_fp fila, int k);
void insere(p_fp fila, Sobrevivente sobrevivente);
Sobrevivente extraiMax(p_fp fila);
void mudaPrioridade(p_fp fila, int k, int aumentoDias);