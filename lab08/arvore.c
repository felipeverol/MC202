#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "arvore.h"

/* Variável global que diz se houve alguma redução na árvore */
bool reduziu;

/* Retorna true caso o caractere seja um operador ou falso caso contrário */
bool operador(char c){
    if(c == '>' || c == '<' || c == '}' || c == '{' || c == '&' || c == '|' || c == '=' || c == '!')
        return true;
    else
        return false;
}

/* Aloca recursivamente os nós da árvore */
p_no criaArvore(p_pilha p){
    p_no r = malloc(sizeof(struct no));
    r->dado = desempilha(p);
    if(operador(r->dado)){
        r->dir = criaArvore(p);
        r->esq = criaArvore(p);
    }else if(!operador(r->dado)){
        r->dir = NULL;
        r->esq = NULL;
    }

    return r;
}

/* Printa a árvora formatada percorrendo a árvore em inordem */
void printaInordem(p_no raiz) {
    if(raiz != NULL){
        if(operador(raiz->dado)){
            printf("(");
            printaInordem(raiz->esq);
            printf(" %c ", raiz->dado); 
            printaInordem(raiz->dir);
            printf(")");
        } else
            printf("%c", raiz->dado); 
    }
}

/* Verifica todos os casos possíveis de relação entre duas folhas de uma raíz e, 
   caso alguma redução seja feita, altera o valor da raiz para T ou F, 
   altera o valor da variável mudou e a retorna */
bool verifica(p_no raiz){
    bool mudou = true;
    
    if(!operador(raiz->dir->dado) || !operador(raiz->esq->dado)){
            if((raiz->dir->dado == 'T' || raiz->esq->dado == 'T') && raiz->dado == '|'){
                raiz->dado = 'T';
            }else if((raiz->dir->dado == 'F' || raiz->esq->dado == 'F') && raiz->dado == '&'){
                raiz->dado = 'F';
            }else if((raiz->dado == '{' && raiz->dir->dado == '9') || (raiz->dado == '}' && raiz->esq->dado == '9')){
                raiz->dado = 'T';
            }else if((raiz->dado == '}' && raiz->dir->dado == '0') || (raiz->dado == '{' && raiz->esq->dado == '0')){
                raiz->dado = 'T';
            }else if((isalpha(raiz->esq->dado) && raiz->dado == '>' && raiz->dir->dado == '9') || 
                     (isalpha(raiz->dir->dado) && raiz->dado == '<' && raiz->esq->dado == '9')){
                raiz->dado = 'F';
            }else if((isalpha(raiz->esq->dado) && raiz->dado == '<' && raiz->dir->dado == '0') || 
                     (isalpha(raiz->dir->dado) && raiz->dado == '>' && raiz->esq->dado == '0')){
                raiz->dado = 'F';
            }else if(raiz->dir->dado == raiz->esq->dado && (raiz->dado == '<' || raiz->dado == '>' || raiz->dado == '!')){
                raiz->dado = 'F';
            }else if(raiz->dir->dado == raiz->esq->dado && (raiz->dado == '{' || raiz->dado == '}' || raiz->dado == '=')){
                raiz->dado = 'T';
            }else if(isdigit(raiz->esq->dado) && isdigit(raiz->dir->dado)){
                    int num1 = raiz->esq->dado - '0';
                    int num2 = raiz->dir->dado - '0';
                    
                    if(num1 > num2 && raiz->dado == '>'){
                        raiz->dado = 'T';
                    }else if(num1 < num2 && raiz->dado == '>'){
                        raiz->dado = 'F';
                    }else if(num1 < num2 && raiz->dado == '<'){
                        raiz->dado = 'T';
                    }else if(num1 > num2 && raiz->dado == '<'){
                        raiz->dado = 'F';
                    }else if(num1 >= num2 && raiz->dado == '}'){
                        raiz->dado = 'T';
                    }else if(num1 < num2 && raiz->dado == '}'){
                        raiz->dado = 'F';
                    }else if(num1 <= num2 && raiz->dado == '{'){
                        raiz->dado = 'T';
                    }else if(num1 > num2 && raiz->dado == '{'){
                        raiz->dado = 'F';
                    }else if(num1 == num2 && raiz->dado == '='){
                        raiz->dado = 'T';
                    }else if(num1 != num2 && raiz->dado == '='){
                        raiz->dado = 'F';
                    }else if(num1 != num2 && raiz->dado == '!'){
                        raiz->dado = 'T';
                    }else if(num1 == num2 && raiz->dado == '!'){
                        raiz->dado = 'F';
                    }else 
                        mudou = false;
            }else
                mudou = false;
        return mudou;
    }
    
    return !mudou;
}

/* Reduz recursivamente a árvore, caso necessário. Caso a varíavel mudou, 
   retornada de verifica(), seja true, a variavel global reduziu se torna 
   true e não é mais alterada, sinalizando que houve uma redução e que 
   podem haver outras */
void reduz(p_no raiz){
        bool mudou;

        if(raiz->dir->dir != NULL && raiz->esq->dir != NULL){
            reduz(raiz->esq);
            mudou = verifica(raiz);
            reduz(raiz->dir);
        } else{
            mudou = verifica(raiz);
            if(mudou == true)
                reduziu = true;
        }
}

/* Libera a árvora através de percurso em pós-ordem */
void liberaAB(p_no raiz) {
    if (raiz != NULL) {
        liberaAB(raiz->esq);
        liberaAB(raiz->dir);
        free(raiz);
        raiz = NULL;
    }
}

/* Retorna o valor de reduziu */
bool retornaReduziu(){
    return reduziu;
}

/* Altera o valor de reduziu */
void alteraReduziu(bool valor){
    reduziu = valor;
}