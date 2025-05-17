#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arvore.h"

// Verifica se nó é vermelho
int ehVermelho(p_no x){
    if(x == NULL)
        return 0;
    return x->cor == VERMELHO;
}

// Verifica se nó é preto
int ehPreto(p_no x){
    if(x == NULL)
        return 1;
    return x->cor == PRETO;
}

// Rotaciona a árvore para a esquerda
p_no rotaciona_para_esquerda(p_no raiz) {
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

// Rotaciona a árvore para a direita
p_no rotaciona_para_direita(p_no raiz) {
    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

// Sobe a cor vermelha para o pai, deixando os filhos pretos
void sobe_vermelho(p_no raiz) {
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

/* Função recursiva que que insere um nó na ABB, de forma que a chave é
   o símbolo e sua prioridade está na ordem alfabética */
p_no inserir_rec(p_no raiz, char simb[], char tipo[]) {
    p_no novo;
    
    if(raiz == NULL) {
        novo = malloc(sizeof(struct no));
        novo->esq = novo->dir = NULL;
        strcpy(novo->simb, simb);
        strcpy(novo->tipo, tipo);
        novo->cor = VERMELHO;
        return novo;
    }
    
    if(strcmp(simb, raiz->simb) < 0)
        raiz->esq = inserir_rec(raiz->esq, simb, tipo);
    else
        raiz->dir = inserir_rec(raiz->dir, simb, tipo);
    
    /* Correções na árvore após inserção */
    if (ehVermelho(raiz->dir) && ehPreto(raiz->esq))
        raiz = rotaciona_para_esquerda(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq))
        raiz = rotaciona_para_direita(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir))
        sobe_vermelho(raiz);
    
    return raiz;
}

// Chama a função 'inserir_rec' e mantém a raiz preta
p_no inserir(p_no raiz, char simb[], char tipo[]) {
    raiz = inserir_rec(raiz, simb, tipo);
    raiz->cor = PRETO;
    return raiz;
}

/* Executa uma busca recursiva por uma chave(símbolo) específico 
   através da ordem alfabética */
p_no buscar(p_no raiz, char simb[]) {
    if(raiz == NULL || strcmp(simb, raiz->simb) == 0)
        return raiz;
    if(strcmp(simb, raiz->simb) < 0)
        return buscar(raiz->esq, simb);
    else
        return buscar(raiz->dir, simb);
}

// Verifica se a primeira palavra de um comando é 'int', 'double' ou 'char'
int ehTipo(char x[MAX]){
    return strcmp(x, "int") == 0 || strcmp(x, "double") == 0 || strcmp(x, "char") == 0;
}

/* Verifica se há parenteses no comando e se o comando não começa com letra.
   Caso positivo, retorna falso e, caso contrário, retorna verdadeiro */
int verificaComando(char buffer[MAX], char c){
    int tam = strlen(buffer);
    for(int i = 0; i < tam; i++)
        if(buffer[i] == '(')
            return 0;

    if(!isalpha(c))
        return 0;

    return 1;
}

/* Percorre a árvore em ordem alfabética por meio do percursso 'inordem' */
void printa(p_no raiz) {
    if (raiz != NULL) {
        printa(raiz->esq);
        printf("%s %s\n", raiz->simb, raiz->tipo);
        printa(raiz->dir);
    }
    free(raiz); // após printar e verificar os filhos de um nó, o livra da memória
}