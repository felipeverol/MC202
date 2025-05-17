#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

struct partida *le_partida(int id){
    struct partida *partida = malloc(sizeof(struct partida));
    struct circuito *c;
     
    /* Adiciona todos os dados relacionados a partida, usando a função le_circuito */
    scanf("%d ", &partida->n_participantes);
    scanf("%d ", &partida->n_circuitos);
    scanf("%d ", &partida->n_equipamentos);

    partida->circuitos = malloc(partida->n_circuitos * sizeof(struct circuito));
    for(int i = 0; i < partida->n_circuitos; i++){
        c = le_circuito(partida->n_participantes);
        partida->circuitos[i] = *c;
        /* Limpa ponteiro auxiliar */
        free(c);
    }

    partida->aluguel = 10 * partida->n_circuitos + 17.5 * partida->n_equipamentos;
    partida->id_partida = id;

    /* Retorna o ponteiro partida */
    return partida;
}

void imprime_partida(struct partida *partida){
    int soma_jogadas;
    
    /* Printa informações da partida */
    printf("Partida %d\n", partida->id_partida);
    printf("Num. de Jogadores: %d - Num. de Circuitos: %d - Num. de Equipamentos: %d\n", 
    partida->n_participantes, partida->n_circuitos, partida->n_equipamentos);
    printf("Valor do Aluguel: R$ %.2f\n", partida->aluguel);

    /* Calcula a soma das jogadas de cada jogador e printa */
    for(int i = 0; i < partida->n_participantes; i++){
        soma_jogadas = 0;
        for(int j = 0; j < partida->n_circuitos; j++){
            soma_jogadas += partida->circuitos[j].n_jogadas[i];
        }
        printf("Jogador %d: %d\n", i + 1, soma_jogadas);
    }

    printf("Circuito mais dificil: %d\n", achar_mais_dificil(partida));
    printf("##########\n");
}

int achar_mais_dificil(struct partida *partida){
    int soma_jogadas, mais_dificil;
    int soma_mais_dificil = 0;

    /* Acha o circuito mais dificil e retorna seu número */
    for(int i = 0; i < partida->n_circuitos; i++){
        soma_jogadas = 0;
        for(int j = 0; j < partida->n_participantes; j++)
            soma_jogadas += partida->circuitos[i].n_jogadas[j];
        if(soma_jogadas > soma_mais_dificil){
            soma_mais_dificil = soma_jogadas;
            mais_dificil = partida->circuitos[i].id_circuito;
        }
    }
    return mais_dificil;
}