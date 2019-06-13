#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_TABULEIRO 8

#define VAZIO 1
#define BRANCO 2
#define VERMELHO 3
#define REIBRANCO 4
#define REIVERMELHO 5

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

void printCorPeca(int posicao){
    if(posicao%2==0){ // Branco
        printf("\x1B[1;37m");
    }else{ // Vermelho
        printf("\x1B[1;31m");
    }
}

char resetaCorTabuleiro(){
    printf("\x1B[0m");
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
            printCorPeca(tabuleiro[linhas][colunas]);
            printf(" %c ", alimentatabuleiro(tabuleiro[linhas][colunas]));
            resetaCorTabuleiro();
            printf("|");
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
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

void verificaRei(int d[][TAMANHO_TABULEIRO],int jogador,int linha1,int coluna2, int coluna1,int linha2){
    int aux;

    if(jogador == 1){
        if(d[linha2][coluna2] == BRANCO && linha2 == 7 && d[linha1][coluna1] == VAZIO){
            aux = d[linha1][coluna1];
            d[linha2][coluna2] = REIBRANCO;
            d[linha1][coluna1] = VAZIO;
        }
    }
    else if(jogador == 2){
        if(d[linha2][coluna2] == VERMELHO && linha2 == 0 && d[linha1][coluna1] == VAZIO){
            aux = d[linha1][coluna1];
            d[linha2][coluna2] = REIVERMELHO;
            d[linha1][coluna1] = VAZIO;
        }
    }
}


int ehPossivelComer(int tabuleiro[][TAMANHO_TABULEIRO], int jogador, int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino){
    /* Verificar para a linha inicial e coluna inicial se havia uma
        linha destino com coluna destino que era possivel comer alguma peça */


}

void mudaposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha1, int coluna1, int linha2, int coluna2){
    int aux;

    aux = tabuleiro[linha1][coluna1];

    tabuleiro[linha1][coluna1] = tabuleiro[linha2][coluna2];

    tabuleiro[linha2][coluna2] = aux;
}

/**
 * Função que valida o movimento para ambos os reis
 * return int - Pode realizar o movimento (1) ou não (0)
 * 
 */
int movimentoValidoReis(int tabuleiro[][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino){
    
    int incrementoI,incrementoJ,linhaAuxiliar, colunaAuxiliar;

    // Variáveis de incremento dependendo de para qual posição o jogador pretende movimentar seu rei
    if(linhaDestino>linhaInicial && colunaDestino>colunaInicial){
        incrementoI = 1;
        incrementoJ = 1;
    }
    else if(linhaDestino>linhaInicial && colunaDestino<colunaInicial){
        incrementoI=1;
        incrementoJ=-1;
    }
    else if(linhaDestino<linhaInicial && colunaDestino < colunaInicial){
        incrementoI=-1;
        incrementoJ=-1;
    }
    else if(linhaDestino<linhaInicial && colunaDestino > colunaInicial){
        incrementoI=-1;
        incrementoJ=1;
    }

    linhaAuxiliar = linhaInicial;
    colunaAuxiliar = colunaInicial;

    // Anda uma posição para sair da inicial
    linhaAuxiliar+=incrementoI;
    colunaAuxiliar+=incrementoJ;

    int quantasPecasInimigasTomou=0;
    while(linhaAuxiliar!=linhaDestino && colunaAuxiliar!=colunaDestino){
        if(
            (tabuleiro[linhaInicial][colunaInicial]==REIBRANCO &&
            (tabuleiro[linhaAuxiliar][colunaAuxiliar]==BRANCO || 
           tabuleiro[linhaAuxiliar][colunaAuxiliar]==REIBRANCO))
           ||
            (tabuleiro[linhaInicial][colunaInicial]==REIVERMELHO &&
            (tabuleiro[linhaAuxiliar][colunaAuxiliar]==VERMELHO || 
           tabuleiro[linhaAuxiliar][colunaAuxiliar]==REIVERMELHO))
           )
           {
            printf("\nVocê não pode pular sobre suas peças! Tente novamente. \n"); // @TODO: Ajustar isso
            return 0; // Não pode prosseguir, encontrou peça igual a sua
        }

        // Verificação para caso tenha tomado mais de 1 peça inimiga
        if((tabuleiro[linhaInicial][colunaInicial]==REIBRANCO &&
            (tabuleiro[linhaAuxiliar][colunaAuxiliar]==VERMELHO || tabuleiro[linhaAuxiliar][colunaAuxiliar]==REIVERMELHO))
            ||
            ((tabuleiro[linhaInicial][colunaInicial]==REIVERMELHO) &&
            (tabuleiro[linhaAuxiliar][colunaAuxiliar]==BRANCO || tabuleiro[linhaAuxiliar][colunaAuxiliar]==REIBRANCO))
        ){
            quantasPecasInimigasTomou++;
        }
        
        
        linhaAuxiliar+=incrementoI;
        colunaAuxiliar+=incrementoJ;
    }
    if(quantasPecasInimigasTomou>1){
        printf("Só pode tomar uma peça inimiga na jogada. Se você pode tomar mais, após a primeira \n você poderá continuar jogando e comendo peças enquanto necessário.");
        return 0;
    }

    linhaAuxiliar = linhaInicial;
    colunaAuxiliar = colunaInicial;

    // Anda uma posição para sair da inicial
    linhaAuxiliar+=incrementoI;
    colunaAuxiliar+=incrementoJ;

    while(linhaAuxiliar!=linhaDestino && colunaAuxiliar!=colunaDestino){
        tabuleiro[linhaAuxiliar][colunaAuxiliar]=1;

        linhaAuxiliar+=incrementoI;
        colunaAuxiliar+=incrementoJ;
    }

    // Se chegou aqui já mudou as peças do tabuleiro e poderá mover a peça rei
    return 1;
            
}

// @TODO: Aqui colocar a validação se comeu uma peça inimiga
// Essa função poderia retornar a mensagem ou printar a mensagem na tela
int movimentoValido(int tabuleiro[][TAMANHO_TABULEIRO], int jogador, int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino){

    // É quem joga, aí avalia os arredores se pode
    if(((tabuleiro[linhaInicial][colunaInicial]==BRANCO || tabuleiro[linhaInicial][colunaInicial]==REIBRANCO) && jogador == 1) ||
       ((tabuleiro[linhaInicial][colunaInicial]==VERMELHO || tabuleiro[linhaInicial][colunaInicial]==REIVERMELHO) && jogador == 2)){

        // @TODO: Refatorar em um mesmo teste
        if(linhaInicial==linhaDestino && colunaInicial==colunaDestino){
            printf("Você esta tentando movimentar para o mesmo lugar! Jogada invalida.\n");
            return 0; // Tenta movimentar pro mesmo lugar, logo, é inválido.
        }

        if(linhaDestino>TAMANHO_TABULEIRO || linhaDestino<0 || colunaDestino>TAMANHO_TABULEIRO || colunaDestino<0){
            printf("Você esta tentando movimentar para fora do tabuleiro! Jogada invalida.\n");
            return 0; // Tenta movimentar para fora do tabuleiro, logo, é inválido
        }

        // Checa se o jogador esta movendo sua propria peça
        if(jogador == 1){
            if(tabuleiro[linhaInicial][colunaInicial] != BRANCO && tabuleiro[linhaInicial][colunaInicial] != REIBRANCO){
                printf("Mova sua propria peça.\n");
                return 0;
            }
        } //Jogador 2
        else if(tabuleiro[linhaInicial][colunaInicial] != VERMELHO && tabuleiro[linhaInicial][colunaInicial] != REIVERMELHO){
                printf("Mova sua propria peça.\n");
                return 0;
        }

        // É um espaço vazio para onde vai
        if(tabuleiro[linhaDestino][colunaDestino] == 1 ){

            // Verificação para reis
            if(tabuleiro[linhaInicial][colunaInicial]==REIBRANCO ||
                tabuleiro[linhaInicial][colunaInicial]==REIVERMELHO){
                    return movimentoValidoReis(tabuleiro,linhaInicial, colunaInicial, linhaDestino, colunaDestino);
            }
            // É uma peça comum branca (só movimenta para baixo)
            if(tabuleiro[linhaInicial][colunaInicial] == BRANCO){
                if(linhaDestino < linhaInicial){
                    printf("Você está tentando retroceder com uma peça simples! Jogada inváida.\n");
                    return 0; // Movimento inválido, está tentando voltar
                }
                if(linhaDestino - 1 == linhaInicial && (colunaDestino+1 == colunaInicial || colunaDestino - 1 == colunaInicial)){
                    return 1; // Retorna Válido. Neste ponto não há peça impedindo, é só movimentar.
                }
                else if(linhaDestino - 2 == linhaInicial && (colunaDestino + 2 == colunaInicial || colunaDestino - 2 == colunaInicial)
                && (tabuleiro[linhaDestino - 1][colunaDestino + 1] == VERMELHO || tabuleiro[linhaDestino - 1][colunaDestino + 1]== REIVERMELHO
                || tabuleiro[linhaDestino - 1][colunaDestino - 1] == VERMELHO || tabuleiro[linhaDestino - 1][colunaDestino - 1] == REIVERMELHO)){
                    if(colunaDestino + 2 == colunaInicial){ // @TODO: SE FOR AUMENTAR SCORE, AUMENTA AQUI
                        tabuleiro[linhaDestino - 1][colunaDestino + 1] = 1;
                    }
                    else{
                        tabuleiro[linhaDestino - 1][colunaDestino - 1] = 1;
                    }
                        return 1;
                }
                else{
                    printf("Você está tentando movimentar sua peça para muito longe! Jogada inváida. \n");
                    return 0;
                }
            }

            

            // É uma peça comum vermelha (só movimenta para cima)
            if(tabuleiro[linhaInicial][colunaInicial] == VERMELHO){
                if(linhaDestino > linhaInicial){
                    printf("Você esta tentando retroceder com uma peça simples! Jogada invalida.\n");
                    return 0; // Movimento inválido, está tentando voltar
                }
                if(linhaDestino + 1 == linhaInicial && (colunaDestino + 1 == colunaInicial || colunaDestino - 1 == colunaInicial)){
                    return 1; // Retorna Válido. Neste ponto não há peça impedindo, é só movimentar.
                }
                else if(linhaDestino + 2 == linhaInicial && (colunaDestino + 2 == colunaInicial || colunaDestino - 2 == colunaInicial)
                && (tabuleiro[linhaDestino + 1][colunaDestino + 1]== BRANCO || tabuleiro[linhaDestino + 1][colunaDestino + 1] == REIBRANCO
                || tabuleiro[linhaDestino + 1][colunaDestino - 1] == BRANCO|| tabuleiro[linhaDestino + 1][colunaDestino - 1] == REIBRANCO)){
                    if(colunaDestino + 2 == colunaInicial){ // @TODO: SE FOR AUMENTAR SCORE, AUMENTA AQUI 
                        tabuleiro[linhaDestino + 1][colunaDestino + 1] = 1;
                    }
                    else{
                        tabuleiro[linhaDestino + 1][colunaDestino - 1] = 1;
                    }
                        return 1;
                }
                else{
                    printf("Você esta tentando movimentar sua peça para muito longe! Jogada invalida. \n");
                    return 0;
                }
            }
        }
        else if(tabuleiro[linhaInicial][colunaInicial] == tabuleiro[linhaDestino][colunaDestino]){
            printf("Você está tentando movimentar sua peça para onde há uma peça sua! Jogada inváida. \n");
            return 0;
        }
        else if(tabuleiro[linhaDestino][colunaDestino]==0){
            printf("Damas não se joga assim! Movimento só na diagonal! Jogada inváida. \n");
            return 0;
        }
        else{
            printf("Você está tentando movimentar sua peça para onde há a peça do outro jogador! Jogada inváida. \n");
            return 0;
        }

    }
    else{
        printf("Você está tentando jogar com uma peça que não é a sua! Jogada inváida.");
        return 0;
    }
}

int validacoes(int tabuleiro[][TAMANHO_TABULEIRO], int jogador,int linha1,int coluna1,int linha2,int coluna2){

        if(movimentoValido(tabuleiro, jogador, linha1, coluna1, linha2, coluna2)){
            mudaposicao(tabuleiro,linha1,coluna1,linha2,coluna2);
            verificaRei(tabuleiro, jogador, linha1, coluna2, coluna1, linha2);
        }

    else return 0;

    return 1;
}

int main(){
    int jogar = 1;
    int menu = 0;
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {
    {0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,4,0},
    {0,3,0,1,0,1,0,2},
    {1,0,1,0,2,0,1,0},
    {0,1,0,5,0,2,0,1},
    {1,0,1,0,1,0,3,0},
    {0,1,0,1,0,2,0,3},
	{1,0,3,0,3,0,1,0}};

    // {0,2,0,1,0,2,0,2},
    // {2,0,3,0,2,0,2,0},
    // {0,4,0,2,0,2,0,2},
    // {1,0,1,0,1,0,1,0},
    // {0,1,0,2,0,2,0,1},
    // {3,0,3,0,1,0,3,0},
    // {0,3,0,3,0,1,0,3},
	// {3,0,3,0,3,0,3,0}};

    // Teste do rei branco
    // {0,1,0,1,0,1,0,1},
    // {1,0,1,0,1,0,1,0},
    // {0,2,0,1,0,3,0,2},
    // {1,0,1,0,3,0,1,0},
    // {0,1,0,4,0,2,0,1},
    // {1,0,1,0,1,0,3,0},
    // {0,1,0,1,0,3,0,3},
	// {1,0,3,0,3,0,1,0}};

    

    setlocale(LC_ALL,"Portuguese"); // seta tudo em portugues, dai nao ocorre mais os erros com caracter especial
    fflush(stdin);

    jogar = mostraMenu();
    int linha1, linha2, quemJoga = 1;
    char coluna1, coluna2;

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
        quemJoga++;
        if(quemJoga>2) quemJoga=1;
    }
}
