#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void inicializaJogo(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    inicializaTabuleiro(tabuleiro);
    // @TODO: Inicializar variáveis de jogo
}


int mostraMenu(){

    char resposta[1];
    printf("\n Seja bem vindo ao jogo de Damas Anglo-Americanas");
    printf("\n Deseja jogar como player 1 ou 2? (n para sair)");
    scanf("%c", resposta);

    if(!strcmp(resposta,"1")){
        return 1;
    }else if(!strcmp(resposta,"2")){
        return 2;
    }else{
        return 0;
    }

}



int main(){
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int jogar = 1;
    int menu = 0;

    jogar = mostraMenu();
    if(jogar){
        inicializaJogo(tabuleiro);
        
    }
    while(jogar){
        
        printaTabuleiro(tabuleiro);
        if(menu){
            jogar = mostraMenu();
            if(jogar){
                inicializaJogo(tabuleiro);
            }
        }
    }
}
