#include <stdio.h>
#define MAX 300
#define MAX2 21

int linhas, caracteres, palavras;
char matriz[MAX][MAX], lista_palavras[MAX][MAX2];
int estado[4] = {0, 0, 0, 0};

void verifica_string(char palavra[], char string[], int pos, int indice){
    /* Verifica se a palavra está na string e altera o valor de um dos 
       elementos do vetor estado para 1 caso a palavra esteja presente */
    for(int i = 0; palavra[i] != '\0'; i++){
        if(string[pos + i] == palavra[i])
            estado[indice] = 1;
        else{
            estado[indice] = 0;
            break;
        }
    }
}

void define_strings(char palavra[], int n_linha, int n_coluna){
    int i, j;
    char linha[MAX], coluna[MAX], coluna_invert[MAX], linha_invert[MAX];
    
    /* Define as  quatro strings de linha e coluna, diretas e invertidas */
    for(i = 0; i < caracteres; i++)
        linha[i] = matriz[n_linha][i];
    
    for(i = caracteres - 1, j = 0; i >= 0; i--, j++)
        linha_invert[j] = linha[i];
    
    linha[caracteres] = '\0';
    linha_invert[caracteres] = '\0';

    for(i = 0; i < linhas; i++)
        coluna[i] = matriz[i][n_coluna];

    for(i = linhas - 1, j = 0; i >= 0; i--, j++)
        coluna_invert[j] = coluna[i];

    coluna[linhas] = '\0';
    coluna_invert[linhas] = '\0';

    /* Aplica as funções de verificar uma string */
    verifica_string(palavra, linha, n_coluna, 0);
    verifica_string(palavra, linha_invert, caracteres - n_coluna - 1, 1);
    verifica_string(palavra, coluna, n_linha, 2);
    verifica_string(palavra, coluna_invert, linhas - n_linha - 1, 3);
}

int procura_palavras(char palavra[]){
    /* Localiza a primeira letra da palavra procurada e chama a função ocorre */
    for(int i = 0; i < linhas; i++)
        for(int j = 0; j < caracteres; j++)
            if(matriz[i][j] == palavra[0]){
                define_strings(palavra, i, j);
    /* Printa se a palavra está ou não no texto */
                for(int i = 0; i < 4; i++)
                    if(estado[i] == 1){
                        printf("A palavra %s está no texto!\n", palavra);
                        return 0;
                    }
            }
    printf("A palavra %s não está no texto!\n", palavra);
    return 0;
}

int main(){
    /* Inputs das variáveis */
    scanf("%d %d %d ", &linhas, &caracteres, &palavras);

    for(int i = 0; i < linhas; i++)
        for(int j = 0; j < caracteres; j++)
            scanf("%c ", &matriz[i][j]);

    for(int i = 0; i < palavras; i++)
        scanf("%s ", lista_palavras[i]);

    /* Loop que inicia a procura das palavras desejadas */
    for(int i = 0; i < palavras; i++)
        procura_palavras(lista_palavras[i]);
    
    return 0;
}