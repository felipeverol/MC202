#include <stdio.h>
#include <stdlib.h>

void printa_matriz(int **matriz, int n_linhas){
    /* Printa a matriz */
    for(int i = 0; i < n_linhas; i++){
        for(int j = 0; j < n_linhas; j++)
            printf("%d\t", matriz[i][j]);
        printf("\n");
    }
}

void acha_soma(int **matriz, int n_linhas){
    int maior_soma = -100;
    int inicio[2];

    /* Para os 4 elementos do canto superior esquerdo da matriz, 
       lê os próximos elementos em um range de n_linhas - 1 e os 
       soma, verificando qual das 4 submatrizes possíveis tem 
       maior soma*/
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            int soma = 0;
            for(int x = 0; x < n_linhas - 1; x++)
                for(int y = 0; y < n_linhas - 1; y++)
                    soma += matriz[x+i][y+j];
            if(soma > maior_soma){
                maior_soma = soma;
                inicio[0] = i;
                inicio[1] = j;
            }
        }
    }

    /* Aloca uma matriz auxiliar para guardar os valores
       e os passa para a matriz original */
    
    int **matriz_nova = malloc((n_linhas - 1) * sizeof(int *));
    
    for(int i = 0; i < n_linhas - 1; i++)
        matriz_nova[i] =  malloc((n_linhas - 1) * sizeof(int));

    for(int i = 0; i < n_linhas - 1; i++)
        for(int j = 0; j < n_linhas - 1; j++)
            matriz_nova[i][j] = matriz[i+inicio[0]][j+inicio[1]];

    for(int i = 0; i < n_linhas - 1; i++)
        for(int j = 0; j < n_linhas - 1; j++)
            matriz[i][j] = matriz_nova[i][j];
    
    /* Livra a matriz auxiliar */

    for(int i = 0; i < n_linhas - 1; i++)
        free(matriz_nova[i]);
    free(matriz_nova);
            
    /* Printa a submatriz */
    printf("Conjuntos que precisam de atenção:\n");
    printa_matriz(matriz, n_linhas - 1);
}

int main(){
    int n_linhas, **matriz, n_linhas_ori;
    int alt = 1;

    /* Lê os dados e aloca dinamicamente a matriz */
    scanf("%d", &n_linhas_ori);
    n_linhas = n_linhas_ori;
    matriz = malloc(n_linhas * sizeof(int *));
    
    for(int i = 0; i < n_linhas; i++)
        matriz[i] = malloc(n_linhas * sizeof(int));
    
    for(int i = 0; i < n_linhas; i++)
        for(int j = 0; j < n_linhas; j++)
            scanf("%d", &matriz[i][j]);

    printf("Quadras:\n");
    printa_matriz(matriz, n_linhas);
    
    /* Verifica a codição de n_linhas >= 1 e alt == 1
       para executar um loop */
    do{
        acha_soma(matriz, n_linhas);
        n_linhas--;
        scanf("%d", &alt);
        if(alt == 1){
            int i, j, valor;
            scanf("%d %d %d ", &i, &j, &valor);
            matriz[i][j] = valor;
        }
    }while(alt == 1 && n_linhas != 1);
        
    /* Livra a matriz */
    for(int i = 0; i < n_linhas_ori; i++)
        free(matriz[i]);
    free(matriz);
    
    return 0;
}