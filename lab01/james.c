#include <stdio.h>
#define MAX 10000

int maior_seq, n_maior_seq = 0;

int conta(int valor, int n_pix, int valores_pix[MAX]){
    int i, contador = 0;
    for(i = 0; i < n_pix; i++)
        if(valores_pix[i] == valor)
            contador++;
    return contador;
}

void acha_maior_seq(int n_pix, int valores_pix[MAX]){
    int j = 1;
    int num = valores_pix[0];
    for(int i = 1; i <= n_pix; i++){
        if(valores_pix[i] == num){
            j++;
        } else{
            if(j > maior_seq){
                maior_seq = j;
                n_maior_seq = num;
            }
            j = 1;
            num = valores_pix[i];
        }
    }
}

int main(){
    int n_pix, i;
    scanf("%d ", &n_pix);
    int valores_pix[MAX];
    for(i = 0; i <= n_pix; i++)
        scanf("%d ", &valores_pix[i]);
    valores_pix[n_pix] = 0;

    int qntd5 = conta(5, n_pix, valores_pix);
    int qntd7 = conta(7, n_pix, valores_pix);
    int qntd10 = conta(10, n_pix, valores_pix);

    acha_maior_seq(n_pix, valores_pix);

    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais\n", qntd5, qntd7, qntd10);
    printf("James vendeu %d saladas de %d reais consecutivamente", maior_seq, n_maior_seq);
    
    return 0;
}