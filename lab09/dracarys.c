#include <stdio.h>
#include <string.h>
#include "arvore.h"

int main(){
    /* Definição de variáveis */
    char buffer[MAX], x[MAX], tipo[MAX], simb1[MAX], simb2[MAX], simb3[MAX], op[MAX];
    p_no arvore = NULL;
    p_no no1, no2, no3;
    int contador, erros, tam;

    contador = erros = 0;
    
    // Ciclo infinito até que seja quebrado de dentro
    while(1){
        contador++;
        strcpy(x, "\0");
        fgets(buffer, MAX, stdin); // Lê uma linha
        sscanf(buffer, "%s", x); // Lê primeira palavra linha
        if(verificaComando(buffer, x[0])){
            if(ehTipo(x)){
                sscanf(buffer, "%s %s;", tipo, simb1);
                tam = strlen(simb1);
                simb1[tam - 1] = '\0'; // Retira o ';'
                arvore = inserir(arvore, simb1, tipo); // Insere o elemento na árvore
            } else if(strcmp(x, "return") != 0){ // Verifica se a primeira palavra da linha não é 'return'
                sscanf(buffer, "%s = %s %s %s;", simb1, simb2, op, simb3);
                tam = strlen(simb3);
                simb3[tam - 1] = '\0'; // Retira o ';'
                
                /* Busca cada um dos elementos na árvore para ver se existem e quais os seus tipos
                   para verificar, posteriormente, se as operações são valídas */
                no1 = buscar(arvore, simb1);
                no2 = buscar(arvore, simb2);
                no3 = buscar(arvore, simb3);
                
                if(no1 != NULL && no2 != NULL && no3 != NULL){ 
                    if(strcmp(no2->tipo, no3->tipo) != 0){
                        printf("Linha %d: tipos incompatíveis: %s (%s) %s %s (%s).\n", contador, simb2, no2->tipo, op, simb3, no3->tipo);
                        erros++;
                    } else if(strcmp(no1->tipo, no2->tipo) != 0){ 
                        printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n", contador, simb1, no1->tipo, no2->tipo);
                        erros++;
                    }
                } else if(no1 == NULL){
                    printf("Linha %d: o símbolo %s não foi definido.\n", contador, simb1);
                    erros++; 
                } else if(no2 == NULL){                                                  
                    printf("Linha %d: o símbolo %s não foi definido.\n", contador, simb2); 
                    erros++;
                } else{                                                                  
                    printf("Linha %d: o símbolo %s não foi definido.\n", contador, simb3); 
                    erros++;
                }
            }
        }
        if(feof(stdin)) // Caso o arquivo sendo lido acabe, o ciclo quebra
            break;
    }

    if(erros == 0) // Caso não haja erros
        printf("Não há erros de tipo.\n");

    printa(arvore); // Printa em ordem alfabética os elementos da árvore

    return 0;
}