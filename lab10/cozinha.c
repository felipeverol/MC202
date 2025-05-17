#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

/* Printa a rodada, extraindo o sobrevivente com maior
   prioridade de acordo com o número de panelas disponíveis 
   por rodada. Caso o sobrevivente de prioridade máxima possua
   prioridade 0, nada acontece. */
int fazRodada(p_fp fila, int nPanelas, int rodada){
    int pedidosFeitos = 0;
    
    Sobrevivente sobrevivente;
    
    printf("---- rodada %d ----\n", rodada);
        
    for(int i = 0; i < nPanelas; i++){
        sobrevivente = extraiMax(fila);
        if(sobrevivente.nDiasSobrevividosAtual != 0){
            printf("%s %s %d\n", sobrevivente.nome, sobrevivente.prato, sobrevivente.nDiasSobrevividosAtual);
            strcpy(fila->v[fila->n].prato, "\0");
            mudaPrioridade(fila, fila->n, 0);
            pedidosFeitos++;
        }
    }

    fila->n = fila->tam;

    return pedidosFeitos;
}

int main(){
    int nPanelas, nSobreviventes, mudanca, ID, aumentoDias, rodada, nDiasSobrevividos, pedidos;
    char nome[32];
    char sobrenome[16];
    char comando[7];
    char prato[25];
    
    scanf("%d %d", &nPanelas, &nSobreviventes);
    p_fp fila = criaFilaPrio(nSobreviventes); // Cria uma fila prioritária
    
    /* Crias os sobreviventes no heap de acordo com as entradas */
    for(int i = 0; i < nSobreviventes; i++){
        Sobrevivente sobrevivente;
        
        scanf("%s %s", nome, sobrenome);
        strcat(nome, " "); 
        strcat(nome, sobrenome);
        scanf("%d ", &nDiasSobrevividos);
        
        strcpy(sobrevivente.nome, nome);
        sobrevivente.nDiasSobrevividos = nDiasSobrevividos;
        sobrevivente.nDiasSobrevividosAtual = 0;
        sobrevivente.ID = i;

        insere(fila, sobrevivente);
    }

    scanf("%d ", &mudanca);
    rodada = 1;
    pedidos = 0;

    while(mudanca != 0){
        /* Executa comandos */
        for(int i = 0; i < mudanca; i++){
            scanf("%s ", comando);
            /* Caso o comando seja 'novo' */
            if(comando[0] == 'n'){
                scanf("%d ", &ID);
                fgets(prato, 25, stdin);
                prato[strlen(prato) - 1] = '\0';
                for(int j = 0; j < fila->tam; j++)
                    if(fila->v[j].ID == ID){
                        strcpy(fila->v[j].prato , prato);
                        mudaPrioridade(fila, j, fila->v[j].nDiasSobrevividos);
                        pedidos++;
                        break;
                    }
            /* Caso o comando seja 'altera' */            
            } else if(comando[0] == 'a'){
                scanf("%d %d ", &ID, &aumentoDias);
                for(int j = 0; j < fila->tam; j++)
                    if(fila->v[j].ID == ID){
                        mudaPrioridade(fila, j, fila->v[j].nDiasSobrevividosAtual + aumentoDias);
                        break;
                    }
            }
        }

        pedidos -= fazRodada(fila, nPanelas, rodada); // Executa a rodada
        rodada++;

        scanf("%d ", &mudanca);
        /* Caso a mudança fosse 0, o while principal seria quebrado e nem todos os
           pedidos seriam entregues devido a falta de panelas. Assim, cria-se um novo while
           que só quebrará quando os pedidos restantes forem entregues */
        if(mudanca == 0 && pedidos > 0){
            while(pedidos > 0){
                pedidos -= fazRodada(fila, nPanelas, rodada); // Executa a rodada
                rodada++;
            }
        }
    }

    /* Livra a memória */
    free(fila->v);
    free(fila);

    return 0;
}