#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 8

int inicializaTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    int i,j;
    for(i=0;i<TAMANHO_TABULEIRO;i++)
        for(j=0;j<TAMANHO_TABULEIRO;j++)
            tabuleiro[i][j] = 0;
}

int printaTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    int i,j;
    
    for(i=0;i<TAMANHO_TABULEIRO;i++){
        printf("%d", i);
        for(j=0;j<TAMANHO_TABULEIRO;j++)
            printf(" %d", tabuleiro[i][j]);
        printf("\n");
    }
    printf("  a b c d e f g h\n");
}

int main(){
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    inicializaTabuleiro(tabuleiro);
    printaTabuleiro(tabuleiro);
}
