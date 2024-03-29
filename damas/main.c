#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "driver.h"

/*-----------------------------------------------------*/

#define TAMANHO_TABULEIRO 8

#define VAZIO 1
#define BRANCO 2
#define VERMELHO 3
#define REIBRANCO 4
#define REIVERMELHO 5

#define DEVICE_NAME "/dev/so"      
#define BUF_LEN 1024

/*----------------------------------------------------------------------------*/

typedef struct nodo{
    int linha;
    int coluna;
    int linhaInicial;
    int colunaInicial;
    struct nodo* prox;
}Nodo;

/*----------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------*/

void printCorPeca(int posicao){
    if(posicao%2==0){ // Branco
        printf("\x1B[1;37m");
    }else{ // Vermelho
        printf("\x1B[1;31m");
    }
}

/*----------------------------------------------------------------------------*/

char resetaCorTabuleiro(){
    printf("\x1B[0m");
}

/*----------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------*/

int mostraMenu(){

    int resposta;
    printf("\n Seja bem vindo ao jogo de Damas Anglo-Americanas");
    printf("\n Deseja jogar como player 1 ou 2? (n para sair)");
    scanf("%d", &resposta);

    if(resposta==1) return 1;
    else if(resposta==2) return 2;

    return 0;

}

/*----------------------------------------------------------------------------*/

void verificaRei(int d[][TAMANHO_TABULEIRO],int jogador,int linha1,int coluna1, int linha2,int coluna2){
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

/*----------------------------------------------------------------------------*/

void mudaposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha1, int coluna1, int linha2, int coluna2){
    int aux;

    aux = tabuleiro[linha1][coluna1];

    tabuleiro[linha1][coluna1] = tabuleiro[linha2][coluna2];

    tabuleiro[linha2][coluna2] = aux;
}

/*----------------------------------------------------------------------------*/

int movimentoValido(int tabuleiro[][TAMANHO_TABULEIRO], int jogador, int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino){

    int muitoLongeReis=0;

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
            // É uma peça comum branca (só movimenta para baixo)
            if(tabuleiro[linhaInicial][colunaInicial] == BRANCO ||
            tabuleiro[linhaInicial][colunaInicial] == REIBRANCO || 
            tabuleiro[linhaInicial][colunaInicial] == REIVERMELHO ){
                if(linhaDestino < linhaInicial && tabuleiro[linhaInicial][colunaInicial] == BRANCO){
                    printf("Você está tentando retroceder com uma peça simples! Jogada inválida.\n");
                    return 0; // Movimento inválido, está tentando voltar
                }
                if(linhaDestino - 1 == linhaInicial && (colunaDestino+1 == colunaInicial || colunaDestino - 1 == colunaInicial)){
                    return 1; // Retorna Válido. Neste ponto não há peça impedindo, é só movimentar.
                }
                else if(( (tabuleiro[linhaInicial][colunaInicial] == BRANCO || tabuleiro[linhaInicial][colunaInicial] == REIBRANCO)  && 
                (linhaDestino - 2 == linhaInicial && (colunaDestino + 2 == colunaInicial || colunaDestino - 2 == colunaInicial)
                && (tabuleiro[linhaDestino - 1][colunaDestino + 1] == VERMELHO || tabuleiro[linhaDestino - 1][colunaDestino + 1]== REIVERMELHO
                || tabuleiro[linhaDestino - 1][colunaDestino - 1] == VERMELHO || tabuleiro[linhaDestino - 1][colunaDestino - 1] == REIVERMELHO)) )
                ||
                ( (tabuleiro[linhaInicial][colunaInicial] == REIVERMELHO)  && 
                (linhaDestino - 2 == linhaInicial && (colunaDestino + 2 == colunaInicial || colunaDestino - 2 == colunaInicial)
                && (tabuleiro[linhaDestino - 1][colunaDestino + 1] == BRANCO || tabuleiro[linhaDestino - 1][colunaDestino + 1]== REIBRANCO
                || tabuleiro[linhaDestino - 1][colunaDestino - 1] == BRANCO || tabuleiro[linhaDestino - 1][colunaDestino - 1] == REIBRANCO)) 
                )){
                    if(colunaDestino + 2 == colunaInicial){ // @TODO: SE FOR AUMENTAR SCORE, AUMENTA AQUI
                        tabuleiro[linhaDestino - 1][colunaDestino + 1] = 1;
                    }
                    else{
                        tabuleiro[linhaDestino - 1][colunaDestino - 1] = 1;
                    }
                        return 1;
                }
                else{
                    if(tabuleiro[linhaInicial][colunaInicial] == BRANCO ){
                        printf("Você está tentando movimentar sua peça para muito longe! Jogada inválida. \n");
                        return 0;
                    }else{
                        muitoLongeReis ++;
                    }
                }
            }

            

            // É uma peça comum vermelha (só movimenta para cima)
            if(tabuleiro[linhaInicial][colunaInicial] == VERMELHO || 
            tabuleiro[linhaInicial][colunaInicial] == REIVERMELHO || 
            tabuleiro[linhaInicial][colunaInicial] == REIBRANCO ){
                if((linhaDestino > linhaInicial) && tabuleiro[linhaInicial][colunaInicial] == VERMELHO){
                    printf("Você esta tentando retroceder com uma peça simples! Jogada invalida.\n");
                    return 0; // Movimento inválido, está tentando voltar
                }
                if(linhaDestino + 1 == linhaInicial && (colunaDestino + 1 == colunaInicial || colunaDestino - 1 == colunaInicial)){
                    return 1; // Retorna Válido. Neste ponto não há peça impedindo, é só movimentar.
                }
                else if(
                    ((tabuleiro[linhaInicial][colunaInicial] == VERMELHO || tabuleiro[linhaInicial][colunaInicial] == REIVERMELHO) 
                && (linhaDestino + 2 == linhaInicial && (colunaDestino + 2 == colunaInicial || colunaDestino - 2 == colunaInicial)
                && (tabuleiro[linhaDestino + 1][colunaDestino + 1]== BRANCO || tabuleiro[linhaDestino + 1][colunaDestino + 1] == REIBRANCO
                || tabuleiro[linhaDestino + 1][colunaDestino - 1] == BRANCO|| tabuleiro[linhaDestino + 1][colunaDestino - 1] == REIBRANCO)))
                || (tabuleiro[linhaInicial][colunaInicial] == REIBRANCO && 
                (linhaDestino + 2 == linhaInicial && (colunaDestino + 2 == colunaInicial || colunaDestino - 2 == colunaInicial)
                && (tabuleiro[linhaDestino + 1][colunaDestino + 1]== VERMELHO || tabuleiro[linhaDestino + 1][colunaDestino + 1] == REIVERMELHO
                || tabuleiro[linhaDestino + 1][colunaDestino - 1] == VERMELHO|| tabuleiro[linhaDestino + 1][colunaDestino - 1] == REIVERMELHO))
                )){
                    if(colunaDestino + 2 == colunaInicial){ // @TODO: SE FOR AUMENTAR SCORE, AUMENTA AQUI 
                        tabuleiro[linhaDestino + 1][colunaDestino + 1] = 1;
                    }
                    else{
                        tabuleiro[linhaDestino + 1][colunaDestino - 1] = 1;
                    }
                        return 1;
                }
                else{
                    if(tabuleiro[linhaInicial][colunaInicial] == VERMELHO ){
                        printf("Você está tentando movimentar sua peça para muito longe! Jogada inválida. \n");
                        return 0;
                    }else{
                        muitoLongeReis ++;
                    }
                }
            }
        }
        else if(tabuleiro[linhaInicial][colunaInicial] == tabuleiro[linhaDestino][colunaDestino]){
            printf("Você está tentando movimentar sua peça para onde há uma peça sua! Jogada inválida. \n");
            return 0;
        }
        else if(tabuleiro[linhaDestino][colunaDestino]==0){
            printf("Damas não se joga assim! Movimento só na diagonal! Jogada inválida. \n");
            return 0;
        }
        else{
            printf("Você está tentando movimentar sua peça para onde há a peça do outro jogador! Jogada inválida. \n");
            return 0;
        }

        if(muitoLongeReis==2){
            printf("Você está tentando movimentar sua peça para muito longe! Jogada inválida. \n");
            return 0;
        }

    }
    else{
        printf("Você está tentando jogar com uma peça que não é a sua! Jogada inválida.");
        return 0;
    }
}

/*----------------------------------------------------------------------------*/

int insereNaLista(Nodo **inicioLista, Nodo* novoValor){
    
    if((*inicioLista)==NULL){
        (*inicioLista)=novoValor;
        return 1;
    }

    Nodo* aux = (*inicioLista);

    while(aux->prox!=NULL) aux = aux->prox;
    

    aux->prox = novoValor;

}

int verificaValidadeNoTabuleiroInsereNaLista(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna,Nodo **inicioLista, int linhaInicial, int colunaInicial){
    // printf("\n Verifica validade");
    if((linha)>=0 && (linha)<TAMANHO_TABULEIRO && (((coluna)>=0 && (coluna)<TAMANHO_TABULEIRO) 
        )){
        if(tabuleiro[linha][coluna] == 1){
            // printf("\n Inseriu");
            Nodo * novoNodo = (Nodo*)malloc(sizeof(Nodo));
            novoNodo->linha = linha;
            novoNodo->coluna = coluna;
            novoNodo->linhaInicial = linhaInicial;
            novoNodo->colunaInicial = colunaInicial;
            novoNodo->prox = NULL;
            insereNaLista(inicioLista, novoNodo);
            return 1;
        }
    }
    return 0;
}

/*----------------------------------------------------------------------------*/

int obrigadoATomar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],int jogador,Nodo **inicioLista){
    int i=0,j=0,arredorInimigoI,arredorInimigoJ;

    for(i=0;i<TAMANHO_TABULEIRO;i++){
        for(j=0;j<TAMANHO_TABULEIRO;j++){
            
            if(((tabuleiro[i-1][j-1]==VERMELHO || tabuleiro[i-1][j-1]==REIVERMELHO) && tabuleiro[i][j] == REIBRANCO && jogador==1)
                ||
                ((tabuleiro[i-1][j-1]==BRANCO || tabuleiro[i-1][j-1]==REIBRANCO) && (tabuleiro[i][j] == VERMELHO || tabuleiro[i][j] == REIVERMELHO) && jogador==2)
                ){
                verificaValidadeNoTabuleiroInsereNaLista(tabuleiro,i-2,j-2, inicioLista, i, j);
            }
            if(((tabuleiro[i-1][j+1]==VERMELHO || tabuleiro[i-1][j+1]==REIVERMELHO) && tabuleiro[i][j]==REIBRANCO && jogador==1)
                ||
                (tabuleiro[i-1][j+1]==BRANCO || tabuleiro[i-1][j+1]==REIBRANCO) && (tabuleiro[i][j] == VERMELHO || tabuleiro[i][j] == REIVERMELHO) && jogador==2
                ){
                
                verificaValidadeNoTabuleiroInsereNaLista(tabuleiro,i-2,j+2, inicioLista, i, j);
                
            }
            if(((tabuleiro[i+1][j-1]==VERMELHO || tabuleiro[i+1][j-1]==REIVERMELHO) && (tabuleiro[i][j]==REIBRANCO || tabuleiro[i][j]==BRANCO) && jogador==1)
                ||
                ((tabuleiro[i+1][j-1]==BRANCO || tabuleiro[i+1][j-1]==REIBRANCO) && tabuleiro[i][j] == REIVERMELHO && jogador==2)
                )
                {
                verificaValidadeNoTabuleiroInsereNaLista(tabuleiro,i+2,j-2, inicioLista, i, j);
            }
            if(((tabuleiro[i+1][j+1]==VERMELHO || tabuleiro[i+1][j+1]==REIVERMELHO) && (tabuleiro[i][j]==REIBRANCO || tabuleiro[i][j]==BRANCO ) && jogador==1)
                ||
                ((tabuleiro[i+1][j+1]==BRANCO || tabuleiro[i+1][j+1]==REIBRANCO) && (tabuleiro[i][j] == REIVERMELHO) && jogador==2)
            ){
                verificaValidadeNoTabuleiroInsereNaLista(tabuleiro,i+2,j+2, inicioLista, i, j);
            }

        }
    }
    return 0;
}

/*----------------------------------------------------------------------------*/

int validaMovimentoObrigatorio(Nodo* inicioLista, int linhaDestino,int colunaDestino, int linhaInicial, int colunaInicial){
    Nodo *aux = inicioLista;
    int i=0;
    while(aux!=NULL){
        if(aux->linha==linhaDestino && aux->coluna==colunaDestino && aux->linhaInicial == linhaInicial && aux->colunaInicial == colunaInicial){
            return 1;
        }
        aux = aux->prox;
    }
    printf("Há uma ou mais peças a serem tomadas mas você não está realizando um movimento que pode tomar peças! Tente novamente \n");
    return 0;
}

/*----------------------------------------------------------------------------*/

int verificaSeAcabou(int tabuleiro[][TAMANHO_TABULEIRO], int jogador){

    int i, j;
    int contJog1=0, contJog2=0;

    for (i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        for (j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            if(tabuleiro[i][j] == 2 || tabuleiro[i][j] == 4) contJog1++;
            else if (tabuleiro[i][j] == 3 || tabuleiro[i][j] == 5) contJog2++;
        }
    }

    int quemGanhou = 0;

    if(!contJog1) quemGanhou = 2; 
    else if (!contJog2) quemGanhou = 1;
    
    return quemGanhou;
}

/*----------------------------------------------------------------------------*/

void limpaLista(Nodo* inicioLista){
    Nodo *aux;
    while (inicioLista != NULL) {
        aux = inicioLista;
        inicioLista = inicioLista->prox;
        free (aux);
    }
}

int validacoes(int tabuleiro[][TAMANHO_TABULEIRO], int jogador,int linha1,int coluna1,int linhaDestino,int colunaDestino){

    Nodo * inicioLista = (Nodo*)malloc(sizeof(Nodo));
    
    inicioLista=NULL;
    obrigadoATomar(tabuleiro,jogador, &inicioLista);

    if(inicioLista!=NULL){
        if(!validaMovimentoObrigatorio(inicioLista, linhaDestino,colunaDestino, linha1, coluna1)){
            limpaLista(inicioLista);
            return 0;
        }
    }

    limpaLista(inicioLista);
    

    if(movimentoValido(tabuleiro, jogador, linha1, coluna1, linhaDestino, colunaDestino)){
        mudaposicao(tabuleiro,linha1,coluna1,linhaDestino,colunaDestino);
        verificaRei(tabuleiro, jogador, linha1,coluna1, linhaDestino, colunaDestino);
    }

    else return 0;

    return 1;
}

/*----------------------------------------------------------------------------*/

void leTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO], char retorno[BUF_LEN]){
    
    int v=0;
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            tabuleiro[i][j] = retorno[v] - '0';
            v++;
        }
    }
}

/*----------------------------------------------------------------------------*/

void montaMensagemIoctl(int tabuleiro[][TAMANHO_TABULEIRO], char matrizString[BUF_LEN], int jogador){

    int v=0;
    for (int z = 0; z < TAMANHO_TABULEIRO; z++)
    {
        for (int h = 0; h < TAMANHO_TABULEIRO; h++)
        {
            matrizString[v] = tabuleiro[z][h] + '0'; 
            v++;
        }
    }

    int ganhou = verificaSeAcabou(tabuleiro, jogador);
    matrizString[v] = ';';
    matrizString[++v] = ganhou + '0';
}

int verificaArquivoTermino(char string[]){
    
    int i;
    for(i = TAMANHO_TABULEIRO*TAMANHO_TABULEIRO; i < BUF_LEN; i++)
        if(string[i] == ';') return string[++i] - '0';
        
    return 0;
}

/*----------------------------------------------------------------------------*/

int main(){
    int jogador, continuarJogando = 1, menu = 0, acabou = 0;
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {
    //{0,1,0,1,0,1,0,1},
    //{1,0,1,0,1,0,1,0},
    //{0,1,0,1,0,1,0,1},
    //{1,0,3,0,3,0,1,0},
    //{0,1,0,3,0,1,0,1},
    //{3,0,3,0,3,0,1,0},
    //{0,3,0,3,0,2,0,3},
	//{3,0,3,0,3,0,3,0}};
    //
    {0,2,0,2,0,2,0,2},
    {2,0,2,0,2,0,2,0},
    {0,2,0,2,0,2,0,2},
    {1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1},
    {3,0,3,0,3,0,3,0},
    {0,3,0,3,0,3,0,3},
	{3,0,3,0,3,0,3,0}};
    
    /* MATRIZ DE FIM DE JOGO */
    
    //{0,1,0,1,0,1,0,1},
    //{1,0,1,0,1,0,1,0},
    //{0,1,0,2,0,1,0,1},
    //{1,0,1,0,3,0,1,0},
    //{0,1,0,1,0,1,0,1},
    //{1,0,1,0,1,0,3,0},
    //{0,1,0,1,0,1,0,1},
    //{1,0,1,0,1,0,1,0}};    
    

    setlocale(LC_ALL,"Portuguese"); // seta tudo em portugues, dai nao ocorre mais os erros com caracter especial
    fflush(stdin);
    
    jogador = mostraMenu();
    int linha1, linha2, quemJoga = 1;
    char coluna1, coluna2;

    int file = open(DEVICE_NAME, O_RDWR);
    char stringRetorno[BUF_LEN], matrizString[BUF_LEN];

    if(file>0){
        montaMensagemIoctl(tabuleiro, matrizString, jogador);
        ioctl(file,  IOCTL_SET_MSG, matrizString);
    }
    else{ // exibe o tabuleiro para o player que entrar por 2o
        printaTabuleiro(tabuleiro);
    }

    while(continuarJogando){
        
        int passou = 0;
        while (file < 0)
        {
            if(!passou){
                printf("\nAguarde o outro jogador terminar sua jogada.\n");
                passou = 1;
            }
            file = open(DEVICE_NAME, O_RDWR);
        }

        int verificou = 0;
        while(file > 0){
            
            if(!verificou){
                ioctl(file, IOCTL_GET_MSG, stringRetorno);
                leTabuleiro(tabuleiro, stringRetorno);
                printaTabuleiro(tabuleiro);
                acabou = verificaArquivoTermino(stringRetorno);
                verificou++;
            }

            if(acabou) break;

            printf("Jogador %d eh a sua vez: ", jogador);
            scanf("%d%c",&linha1,&coluna1);
            printf("para: ");
            scanf("%d%c",&linha2,&coluna2);
            //faz -1 e -a para diminuir, pois a matriz inicia em zero mas para o usuario inicia em 1
            if(validacoes(tabuleiro, jogador, linha1-1,coluna1 - 'a',linha2-1,coluna2 - 'a'))
                break;
            
            printf("Movimento invalido, tente novamente!\n");
        }
        
        montaMensagemIoctl(tabuleiro, matrizString, jogador);
        ioctl(file,  IOCTL_SET_MSG, matrizString);

        ioctl(file, IOCTL_GET_MSG, stringRetorno);
        leTabuleiro(tabuleiro, stringRetorno);
        printaTabuleiro(tabuleiro);

        acabou = !acabou ? verificaArquivoTermino(stringRetorno) : acabou;

        close(file);
        file = -1;
        sleep(1);

        if(acabou>0) continuarJogando = 0;
    }

    if(acabou == jogador) printf("\nParabéns jogador %d, você venceu!\n", jogador);
    else printf("\nMais sorte na próxima vez jogador %d!\n", jogador);
}
