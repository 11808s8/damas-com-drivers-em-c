#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABULEIRO 8


/*int inicializaTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    int i,j;
    for(i=0;i<TAMANHO_TABULEIRO;i++)
        for(j=0;j<TAMANHO_TABULEIRO;j++)
            tabuleiro[i][j] = 0;
}*/

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

/*void inicializaJogo(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]){
    //inicializaTabuleiro(tabuleiro);
    // @TODO: Inicializar variáveis de jogo
}*/


int mostraMenu(){

    int resposta;
    printf("\n Seja bem vindo ao jogo de Damas Anglo-Americanas");
    printf("\n Deseja jogar como player 1 ou 2? (n para sair)");
    scanf("%d", &resposta);

    if(resposta==1) return 1;
    else if(resposta==2) return 2;

    return 0;

}

void mudaposicao(int tabuleiro[][TAMANHO_TABULEIRO], int linha1, int coluna1, int linha2, int coluna2){
    int aux;

    aux = tabuleiro[linha1][coluna1];

    tabuleiro[linha1][coluna1] = tabuleiro[linha2][coluna2];

    tabuleiro[linha2][coluna2] = aux;

}

int validacoes(int tabuleiro[][TAMANHO_TABULEIRO], int jogador,int linha1,int coluna1,int linha2,int coluna2){

    mudaposicao(tabuleiro,linha1,coluna1,linha2,coluna2);

    return 1;
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
    int linha1, linha2;
    char coluna1, coluna2;

    while(jogar){

        printaTabuleiro(tabuleiro);
        while(1){
            printf("Jogador 1 eh a sua vez: ");
            scanf("%d%c",&linha1,&coluna1);
            printf("para: ");
            scanf("%d%c",&linha2,&coluna2);
            //faz -1 e -a para diminuir, pois a matriz inicia em zero mas para o usuario inicia em 1
            if(validacoes(tabuleiro, 1, linha1-1,coluna1 - 'a',linha2-1,coluna2 - 'a'))
                break;
            printf("Movimento invalido, tente novamente!\n");
        }

        printaTabuleiro(tabuleiro);

        while(1){ //Turno do Jogador 2
            printf("Jogador 2 eh a sua vez: ");
            scanf("%d%c",&linha1,&coluna1);
    	    printf("para: ");
        	scanf("%d%c",&linha2,&coluna2);
        	if(validacoes(tabuleiro, 2, linha1-1,coluna1 - 'a',linha2-1,coluna2 - 'a'))
        	    break;
        	printf("Movimento invalido, tente novamente\n"); //Caso o movimento esteja incorreto, volta para o laco de repeticao


        }
    }
}
