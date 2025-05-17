#define MAX 201
enum cor {VERMELHO, PRETO};

typedef struct no* p_no;

struct no{
    char simb[MAX];
    char tipo[MAX];
    enum cor cor;
    p_no esq, dir;
};

int ehVermelho(p_no x);
int ehPreto(p_no x);
p_no rotaciona_para_esquerda(p_no raiz);
p_no rotaciona_para_direita(p_no raiz);
void sobe_vermelho(p_no raiz);
p_no inserir_rec(p_no raiz, char simb[], char tipo[]);
p_no inserir(p_no raiz, char simb[], char tipo[]);
p_no buscar(p_no raiz, char simb[]);
int ehTipo(char x[MAX]);
int verificaComando(char buffer[MAX], char c);
void printa(p_no raiz);
