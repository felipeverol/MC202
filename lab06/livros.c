#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX1 56
#define MAX2 46
#define MAX3 10

typedef struct no* p_no;

/* Define a struct de um nó */
struct no{
    char dado[MAX2];
    p_no prox;
};

/* Adiciona um elemento ao início da lista */
p_no adicionar_inicio(p_no lista, char livro[MAX2]){
    p_no nova_lista = malloc(sizeof(struct no));
    strcpy(nova_lista->dado, livro);
    nova_lista->prox = lista;
    
    return nova_lista;
}

/* Adiciona elementos no meio da lista, entre um elemento e outro,
   após o uso da função adicionar_inicio */
void adicionar_meio(p_no inicio, char livro[MAX2]){
    p_no fim = inicio->prox;
    p_no novo_no = malloc(sizeof(struct no));
    strcpy(novo_no->dado, livro);
    inicio->prox = novo_no;
    novo_no->prox = fim;
}

/* Adiciona elementos no final da lista */
p_no adicionar_final(p_no lista, char livro[MAX2]){
    p_no nova_lista = malloc(sizeof(struct no));
    strcpy(nova_lista->dado, livro);
    nova_lista->prox = NULL;

    if(lista == NULL){
        free(lista);
        return nova_lista;
    } else{
        p_no elemento = lista;
        
        while(elemento->prox != NULL)
            elemento = elemento->prox;
        
        elemento->prox = nova_lista;
        return lista;
    }
}

/* Imprime a lista */
void imprimir(p_no lista){
    p_no atual;
    for(atual = lista; atual->prox != NULL; atual = atual->prox)
        printf("%s, ", atual->dado);
    printf("%s\n", atual->dado);
}

/* Remove um item da lista */
p_no remover(p_no lista, char livro[MAX2], int verif, int *estado_add){
    int i = 0;
    p_no elemento = lista;
    p_no anterior;
    while(strcmp(elemento->dado, livro) != 0){
        i++;
        anterior = elemento;
        elemento = elemento->prox;
    }
    if(i == 0){
        /* A variável verif, se igual a 1, indica que o elemento removido
           é o primeiro e que acabou de ser adicionado, sinalizando que o
           programa deve voltar ao estado de adição 1 (adicionar no início) */
        if(verif == 1)
            *estado_add = 1;
        p_no proximo = lista->prox;
        free(lista);
        return proximo;
    } else
        anterior->prox = elemento->prox;
    
    free(elemento);
    return lista;
}

int main(){
    /* Define as variáveis */
    int estado_add, verif;
    char livro[MAX2];
    char comando[MAX3];

    p_no lista = NULL;
    p_no elemento;
    estado_add = 0;
    verif = 0;

    /* Loop principal */
    while(scanf("%s ", comando) != EOF){
        if(strcmp(comando, "adicionar") == 0){
            fgets(livro, MAX2, stdin);
            livro[strlen(livro) - 1] = '\0';
            if(estado_add == 0)
                lista = adicionar_final(lista, livro);
            else if(estado_add == 1){
                lista = adicionar_inicio(lista, livro);
                elemento = lista;
                verif = 1;
                estado_add = 2;
            }
            else if(estado_add == 2){
                adicionar_meio(elemento, livro);
                elemento = elemento->prox;
                verif = 0;
            }
        } else if(strcmp(comando, "inicio") == 0){
            estado_add = 1;
        } else if(strcmp(comando, "final") == 0){
            estado_add = 0;
        } else if(strcmp(comando, "remover") == 0){
            fgets(livro, MAX2, stdin);
            livro[strlen(livro) - 1] = '\0';
            lista = remover(lista, livro, verif, &estado_add);
        } else if(strcmp(comando, "imprimir") == 0){
            imprimir(lista);
        }
        
    }

    /* Livra a memória */
    elemento = lista;
    while(elemento != NULL){
        p_no proximo = elemento->prox;
        free(elemento);
        elemento = proximo;
    }
}