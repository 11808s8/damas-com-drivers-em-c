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
// Essa função poderia retornar a mensagem ou printar a mensagem na tela
int movimentoValido(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int jogador, int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino){
        
    // É quem joga, aí avalia os arredores se pode
    if(((tabuleiro[linhaInicial][colunaInicial]==2 || tabuleiro[linhaInicial][colunaInicial]==4) && jogador == 1) ||
       ((tabuleiro[linhaInicial][colunaInicial]==3 || tabuleiro[linhaInicial][colunaInicial]==5) && jogador == 2)){
        
        // @TODO: Refatorar em um mesmo teste
        if(linhaInicial==linhaDestino && colunaInicial==colunaDestino){
            printf("Você está tentando movimentar para o mesmo lugar! Jogada inválida.\n");
            return 0; // Tenta movimentar pro mesmo lugar, logo, é inválido.
        }
        
        if(linhaDestino>TAMANHO_TABULEIRO || linhaDestino<0 || colunaDestino>TAMANHO_TABULEIRO || colunaDestino<0){
            printf("Você está tentando movimentar para fora do tabuleiro! Jogada inválida.\n");
            return 0; // Tenta movimentar para fora do tabuleiro, logo, é inválido
        }
        
        // É um espaço vazio para onde vai
        if(tabuleiro[linhaDestino][colunaDestino] == 1 ){
            //  case 1:
            // return ' '; //espaço vazio
            // case 2:
            //     return 'b'; //peça normal branca
            // case 3:
            //     return 'v'; //peça normal vermelha
            // case 4:
            //     return 'B'; //dama branca
            // case 5:
            //     return 'V'; //dama vermelha

            // É uma peça comum branca (só movimenta para baixo)
            if(tabuleiro[linhaInicial][colunaInicial]==2){ 
                if(linhaDestino<linhaInicial){
                    printf("Você está tentando retroceder com uma peça simples! Jogada inválida.\n");
                    return 0; // Movimento inválido, está tentando voltar
                }
                if(linhaDestino-1==linhaInicial && (colunaDestino+1==colunaInicial || colunaDestino-1 == colunaInicial)){
                    return 1; // Retorna Válido. Neste ponto não há peça impedindo, é só movimentar.
                }else if(linhaDestino-2==linhaInicial && (colunaDestino+2==colunaInicial || colunaDestino-2 == colunaInicial)
                && (tabuleiro[linhaDestino-1][colunaDestino+1]==3 || tabuleiro[linhaDestino-1][colunaDestino+1]==5
                || tabuleiro[linhaDestino-1][colunaDestino-1] == 3 || tabuleiro[linhaDestino-1][colunaDestino-1]==5)){
                    if(colunaDestino+2==colunaInicial){ // @TODO: SE FOR AUMENTAR SCORE, AUMENTA AQUI
                        tabuleiro[linhaDestino-1][colunaDestino+1]=1;
                    }else{
                        tabuleiro[linhaDestino-1][colunaDestino-1]=1;
                    }
                        return 1;
                }else{
                    printf("Você está tentando movimentar sua peça para muito longe! Jogada inválida. \n");
                    return 0;
                }
                    
            }

            // É uma peça comum vermelha (só movimenta para cima)
            if(tabuleiro[linhaInicial][colunaInicial]==3){ 
                if(linhaDestino>linhaInicial){
                    printf("Você está tentando retroceder com uma peça simples! Jogada inválida.\n");
                    return 0; // Movimento inválido, está tentando voltar
                }
                if(linhaDestino+1==linhaInicial && (colunaDestino+1==colunaInicial || colunaDestino-1 == colunaInicial)){
                    return 1; // Retorna Válido. Neste ponto não há peça impedindo, é só movimentar.
                }else if(linhaDestino+2==linhaInicial && (colunaDestino+2==colunaInicial || colunaDestino-2 == colunaInicial)
                && (tabuleiro[linhaDestino+1][colunaDestino+1]==2 || tabuleiro[linhaDestino+1][colunaDestino+1]==4
                || tabuleiro[linhaDestino+1][colunaDestino-1] ==2 || tabuleiro[linhaDestino+1][colunaDestino-1]==4)){
                    if(colunaDestino+2==colunaInicial){ // @TODO: SE FOR AUMENTAR SCORE, AUMENTA AQUI
                        tabuleiro[linhaDestino+1][colunaDestino+1]=1;
                    }else{
                        tabuleiro[linhaDestino+1][colunaDestino-1]=1;
                    }
                        return 1;
                }else{
                    printf("Você está tentando movimentar sua peça para muito longe! Jogada inválida. \n");
                    return 0;
                }
            }
        }else if(tabuleiro[linhaInicial][colunaInicial] == tabuleiro[linhaDestino][colunaDestino]){
            printf("Você está tentando movimentar sua peça para onde há uma peça sua! Jogada inválida. \n");
            return 0;
        }else if(tabuleiro[linhaDestino][colunaDestino]==0){
            printf("Damas não se joga assim! Movimento só na diagonal! Jogada inválida. \n");
            return 0;
        }else{
            printf("Você está tentando movimentar sua peça para onde há a peça do outro jogador! Jogada inválida. \n");
            return 0;
        }

    }else{
        printf("Você está tentando jogar com uma peça que não é a sua! Jogada inválida.");
        return 0;
    }

}

int validacoes(int tabuleiro[][TAMANHO_TABULEIRO], int jogador,int linha1,int coluna1,int linha2,int coluna2){

    // if(validaMovimento(linha1,coluna1,linha2,coluna2)){
        if(movimentoValido(tabuleiro, jogador, linha1,coluna1,linha2,coluna2)){
            mudaposicao(tabuleiro,linha1,coluna1,linha2,coluna2);
        }else{
            return 0;
        }
        
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
    {0,1,0,2,0,2,0,1},
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
            if(validacoes(tabuleiro, quemJoga, linha1-1,coluna1 - 'a',linha2-1,coluna2 - 'a'))
                break;
            printf("Movimento invalido, tente novamente!\n");
        }
        quemJoga ++;
        if(quemJoga>2)
            quemJoga=1;
    }
}
