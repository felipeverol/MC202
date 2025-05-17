#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"

int main(){
    /* Definição de variáveis */
    int numEntradas;
    p_pilha pilha;
    p_no arvore;

    /* Leitura do número de entradas e criação da pilha */
    scanf("%d ", &numEntradas);
    pilha = criaPilha();
    
    for(int i = 0; i < numEntradas; i++){
        char elemento;
        
        /* Empilha os caracteres digitados na pilha */        
        do{
            scanf("%c", &elemento);
            empilha(pilha, elemento);
        }while(elemento != '\n');
        
        
        desempilha(pilha); // Desempilha o caractere '\n' 
        arvore = criaArvore(pilha); // Cria a árvore com os elementos da pilha
        printaInordem(arvore); // Printa a árvore sem reduções
        printf("\n");
        
        /* Caso reduziu se mantenha true, a árvore continuará tentando ser reduzida */
        do{
            alteraReduziu(false); // Define reduziu inicialmente como false
            reduz(arvore);
        }while(retornaReduziu() == true);
        
        printaInordem(arvore); // Printa árvore reduzida
        printf("\n\n");
        liberaAB(arvore); // Libera árvore
    }
    
    free(pilha); // Libera a struct pilha alocada
    
    return 0;
}