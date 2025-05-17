#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct memoria{
    int *dados;
    int n;
    int uso;
}memoria;

void bat_alloc(int n, int *vetor, memoria *memoria){
    int contador = 0;
    int inicio;

    /* Verifica se há uma sequência de zeros na memória
       suficientemente grande para alocar o vetor desejado
       e registra a posição de inicio para alocação */
    for(int i = 0; i < memoria->n; i++){
        if(memoria->dados[i] == 0){
            if(contador == 0)
                inicio = i;
            contador++;
            if(contador == n + 1)
                break;
        }else
            contador = 0;
    }

    /* Verifica se há espaço para o vetor e aloca. Caso contrário,
       cria uma "memória auxiliar" com tamanho dobrado e atribui
       o ponteiro da memória original ao da nova memória e chama
       novamente a função */
    if(contador == n + 1){
        memoria->dados[inicio] = n;
        for(int i = 0; i < n; i++){
            memoria->dados[inicio + i + 1] = vetor[i];
        }
        printf("%d\n", inicio);
    } else{
        memoria->n *= 2;
        int *memoria_nova = calloc(memoria->n, sizeof(int));
        for(int i = 0; i < (memoria->n / 2); i++)
            memoria_nova[i] = memoria->dados[i];
        free(memoria->dados);
        memoria->dados = memoria_nova;
        bat_alloc(n, vetor, memoria);
    }
}

void bat_free(int endereco, memoria *memoria){
    int estado = 0;
    int num = memoria->dados[endereco];

    /* Atribui valor 0 ao elemento que deve ser liberado */
    for(int i = 0; i <= num; i++){
        memoria->dados[endereco + i] = 0;
    }
   
    /* Verifica se os últimos 3/4 da memória estão livres.
       Caso estejam, e caso a memória possua tamanha maior
       ou igual a 16, diminui seu tamanho pela metade */
    for(int i = memoria->n / 4; i < memoria->n; i++){
        if(memoria->dados[i] != 0){
            estado = 1;
            break;
        }
    }
    if(estado == 0 && memoria->n >= 16){
        memoria->n /= 2;
        int *memoria_nova = calloc(memoria->n, sizeof(int));
        for(int i = 0; i < (memoria->n / 2); i++)
            memoria_nova[i] = memoria->dados[i];
        free(memoria->dados);
        memoria->dados = memoria_nova;
    }
}

void bat_print(int endereco, memoria *memoria){
    /* Printa trecho da memória a partir do elemento pedido */
    for(int i = 0; i < memoria->dados[endereco]; i++)
        printf("%d ", memoria->dados[endereco + i + 1]);
    printf("\n");
}

void bat_uso(memoria *memoria){
    /* Conta a quantidade de elementos diferentes de zero e printa */
    memoria->uso = 0;
    for(int i = 0; i < memoria->n; i++)
        if(memoria->dados[i] != 0)
            memoria->uso++;
    printf("%d de %d\n", memoria->uso, memoria->n);
}

int main(){
    /* Define as váriaveis e struct */
    memoria memoria;
    char comando[10];
    int instrucoes;
    memoria.n = 8;

    memoria.dados = calloc(memoria.n, sizeof(int));
    scanf("%d", &instrucoes);

    /* Loop para execução das intruções */
    for(int i = 0; i < instrucoes; i++){
        scanf("%s", comando);
        if(strcmp(comando, "bat-alloc") == 0){
            int n;
            int *vetor;
            scanf("%d", &n);
            vetor = malloc(n * sizeof(int));
            for(int i = 0; i < n; i++)
                scanf("%d", &vetor[i]);
            bat_alloc(n, vetor, &memoria);
            free(vetor);
        } else if(strcmp(comando, "bat-free") == 0){
            int endereco;
            scanf("%d", &endereco);
            bat_free(endereco, &memoria);
        } else if(strcmp(comando, "bat-print") == 0){
            int endereco;
            scanf("%d", &endereco);
            bat_print(endereco, &memoria);
        } else if(strcmp(comando, "bat-uso") == 0){
            bat_uso(&memoria);
        }
    }
    /* Livra a memória */
    free(memoria.dados);
    return 0;
}
