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

char alimentatabuleiro(int posicao){

    switch(posicao)
    {
  	case 0:
            return ' ';
        case 1:
            return ' '; //espaço vazio
        case 2:
            return 'b'; //peça normal branca
        case 3:
            return 'v'; //peça normal vermelha
        case 4:
            return 'B'; //dama branca
        case 5:
            return 'V'; //dama vermelha
    }
    return ('?');
}

int printaTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    int linhas, colunas;
    printf("\n");
    printf("    a   b   c   d   e   f   g   h\n"); //Colunas
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (linhas=0; linhas<TAMANHO_TABULEIRO; ++linhas)
    {
        printf("%d |", linhas+1); //Linhas

        for (colunas=0; colunas<TAMANHO_TABULEIRO; ++colunas) //Tamanho do tabuleiro
        {
            printf(" %c |", alimentatabuleiro(tabuleiro[linhas][colunas]));
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
}

void inicializaJogo(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    //inicializaTabuleiro(tabuleiro);
    // @TODO: Inicializar variáveis de jogo
}


int mostraMenu(){

    int resposta;
    printf("\n Seja bem vindo ao jogo de Damas Anglo-Americanas");
    printf("\n Deseja jogar como player 1 ou 2? (n para sair)");
    scanf("%d", &resposta);

    if(resposta==1) return 1;
    else if(resposta==2) return 2;

    return 0;

}

int main(){
    int jogar = 1;
    int menu = 0;
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {
    {0,2,0,2,0,2,0,2},
    {2,0,2,0,2,0,2,0},
    {0,2,0,2,0,2,0,2},
    {1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1},
    {3,0,3,0,3,0,3,0},
    {0,3,0,3,0,3,0,3},
	{3,0,3,0,3,0,3,0}};


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
        break;
    }
}
