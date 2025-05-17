#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(){
    int op, u, v, *pai;
    p_grafo grafo = criar_grafo(20);

    while(1){
        scanf("%d ", &op);
        if(op == 1){
            scanf("%d ", &u);
        } else if(op == 2){
            scanf("%d %d ", &u, &v);
            insere_aresta(grafo, u, v);
        } else if(op == 3){
            scanf("%d %d ", &u, &v);
            remove_aresta(grafo, u, v);
        } else if(op == 4){
            scanf("%d %d ", &u, &v);
            if(existe_caminho(grafo, u, v))
                printf("Existe conexão entre os nós.");
            else
                printf("Não existe conexão entre os nós.");
        } else if(op == 5){
            scanf("%d %d", &u, &v);
            pai = busca_em_largura(grafo, u, v);
            if(pai != NULL){
                imprimir_caminho(v, pai);
                free(pai);
            } else
                printf("Não existe conexão entre os nós.");
        } else if(op == 6){
            for(int i = 1; i <= grafo->n; i++){
                printf("Ponto X (Pontos diretamente ou indiretamente conectados):");
                for(int j = 1; j <= grafo->n; j++){
                    if(existe_caminho(grafo, i, j))
                        printf(" %d", j);
                }
            }
         } else
            break;
    }    
    
    return 0;
}