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

void mudaposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha1, int coluna1, int linha2, int coluna2){
    int aux;

    aux = tabuleiro[linha1][coluna1];

    tabuleiro[linha1][coluna1] = tabuleiro[linha2][coluna2];

    tabuleiro[linha2][coluna2] = aux;

}

// @TODO: Aqui colocar a validação se comeu uma peça inimiga
int movimentoValido(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int jogador, int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino, int quemJoga){
        
    // É quem joga, aí avalia os arredores se pode
    if(tabuleiro[linhaInicial][colunaInicial]==quemJoga || tabuleiro[linhaInicial][colunaInicial]==quemJoga+2){
        if(tabuleiro[linhaDestino][colunaDestino] == 0 && 
        (tabuleiro[linhaDestino][colunaDestino+1] ||
        tabuleiro[linhaDestino-1][colunaDestino-1] ||
        tabuleiro[linhaDestino][colunaDestino+1] ||)
        tabuleiro[linhaDestino+1][colunaDestino] ||){

        }
        if(tabuleiro[i+1][j+1]==1 || tabuleiro[i-1][j-1]==1 || tabuleiro[i+1][j-1]==1 || tabuleiro[i-1][j+1]==1){

        }
    }

}

int validacoes(int tabuleiro[][TAMANHO_TABULEIRO], int jogador,int linha1,int coluna1,int linha2,int coluna2){

    // if(validaMovimento(linha1,coluna1,linha2,coluna2)){
        movimentoValido(tabuleiro, jogador, linha1,coluna1,linha2,coluna2);
        mudaposicao(tabuleiro,linha1,coluna1,linha2,coluna2);
        
    // }

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
    int quemJoga = 1;

    while(jogar){

        printaTabuleiro(tabuleiro);
        while(1){
            printf("Jogador %d eh a sua vez: ", quemJoga);
            scanf("%d%c",&linha1,&coluna1);
            printf("para: ");
            scanf("%d%c",&linha2,&coluna2);
            //faz -1 e -a para diminuir, pois a matriz inicia em zero mas para o usuario inicia em 1
            if(validacoes(tabuleiro, quemJoga, linha1-1,coluna1 - 'a',linha2-1,coluna2 - 'a',jogadasPossiveis))
                break;
            printf("Movimento invalido, tente novamente!\n");
        }
        quemJoga ++;
        if(quemJoga>2)
            quemJoga=1;
    }
}
