#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>

// Aqui eu defino uma estrutura para a matriz do jogo
typedef struct {
    char jogue[3][3];
} Matrizl;

// Crio e declaro a matriz global para o jogo
char jogo[3][3];
int l, c;

// Variáveis para contar as vitórias dos jogadores
int vitoriasJogador1 = 0;
int vitoriasJogador2 = 0;

// Função para inicializar a matriz 
void InicializarMatriz() {
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            jogo[l][c] = ' ';
    }
}

// Aqui é uma função para imprimir o tabuleiro do jogo na tela
void ImprimirNaTela() {
    printf("\n\n\t 0   1   2\n\n");
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++) {
            if (c == 0)
                printf("\t");
            printf(" %c ", jogo[l][c]);
            if (c < 2)
                printf("|");
            if (c == 2)
                printf("   %d", l);
        }
        printf("\n");
        if (l < 2)
            printf("\t-----------\n");
    }
}

// Função para verificar se um jogador ganhou em uma linha específica
int GanhouPorLinha(int l, char j) {
    return (jogo[l][0] == j && jogo[l][1] == j && jogo[l][2] == j);
}

// Função para verificar se um jogador ganhou em qualquer linha
int GanhouPorLinhas(char j) {
    int ganhou = 0;
    for (l = 0; l < 3; l++)
        ganhou = ganhou + GanhouPorLinha(l, j);
    return ganhou;
}

// Função para verificar se um jogador ganhou em uma coluna específica
int GanhouPorColuna(int c, char j) {
    return (jogo[0][c] == j && jogo[1][c] == j && jogo[2][c] == j);
}

// Função para verificar se um jogador ganhou em qualquer coluna
int GanhouPorColunas(char j) {
    int ganhou = 0;
    for (c = 0; c < 3; c++)
        ganhou = ganhou + GanhouPorColuna(c, j);
    return ganhou;
}

// Função para verificar se um jogador ganhou na diagonal principal
int GanhouPorDiagonalPrincipal(char j) {
    return (jogo[0][0] == j && jogo[1][1] == j && jogo[2][2] == j);
}

// Função para verificar se um jogador ganhou na diagonal secundária
int GanhouPorDiagonalSecundaria(char j) {
    return (jogo[0][2] == j && jogo[1][1] == j && jogo[2][0] == j);
}

// Função para verificar se uma posição é válida na matriz
int ehValida(int l, int c) {
    return (l >= 0 && l < 3 && c >= 0 && c < 3 && jogo[l][c] == ' ');
}

// Função para verificar se a entrada é numérica, para não acontecer problemas com strings
int verificaNumero(char *ilinput) {
    while (*ilinput) {
        if (!isdigit(*ilinput)) {
            return 0; // Retorna 0 se encontrar algum caractere que não é número
        }
        ilinput++;
    }
    return 1; // Retorna 1 se todos os caracteres são números
}

// Aqui eu leio as coordenadas do jogador
void LerCoordenadas(char j) {
    int linha, coluna;
    char ilinput[20]; // Aqui eu defino um tamanho suficiente para armazenar os números digitados como strings

    printf("Jogador %c, digite linha e coluna (numeros de 0 a 2 cada): ", j);

    // Enquanto a entrada não for numérica, continue pedindo ao usuário para digitar novamente(pra não dar bug)
    do {
        scanf("%s", ilinput);
        if (!verificaNumero(ilinput)) {
            printf("Entrada invalida! Digite apenas numeros (0 a 2 cada): ");
        } else {
            linha = atoi(ilinput);//Converter a string para inteiro, para aceitar corretamente caso o erre
            scanf("%s", ilinput);
            if (!verificaNumero(ilinput)) {
                printf("Entrada invalida! Digite apenas numeros (0 a 2 cada): ");
            } else {
                coluna = atoi(ilinput); // Converter a string para inteiro
            }
        }
    } while (!verificaNumero(ilinput));

// Verificar se os números estão no intervalo correto de (0 a 2), pois é as possibilidades no jogo da velha
    while (!ehValida(linha, coluna)) {
        printf("Posicão invalida! Digite outra linha e coluna (numeros de 0 a 2 cada): ");
        scanf("%d%d", &linha, &coluna);
    }
    // Ver e faz o que precisar com os números válidos
    jogo[linha][coluna] = j;
}

// Função que conta a quantidade de posições vazias no tabuleiro
int QuantVazias() {
    int quantidade = 0;
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            if (jogo[l][c] == ' ')
                quantidade++;
    }
    return quantidade;
}

/* Função para a máquina fazer um movimento aleatório (ela randomiza um número aleatório de 0 a 8)
   Essa função nesse programa é para o modo computador e nela o computador escolhe as suas jogadas*/
void FazerMovimentoMaquina(char j) {
    int linha, coluna;
    srand(time(NULL));

    do {
        linha = rand() % 3;
        coluna = rand() % 3;
    } while (!ehValida(linha, coluna));

    jogo[linha][coluna] = j;
}

// Imprime o resultado do jogo
void ImprimirResultado() {
    printf("\nNumero de vitórias do Jogador 1: %d\n", vitoriasJogador1);
    printf("Numero de vitórias do Jogador 2: %d\n", vitoriasJogador2);
}

// Função de jogar, nela será armazenada as jogadas e vitórias das jogadas
void jogar() {
    int jogador = 1, vitoriaX = 0, vitoriaO = 0;
    char jogador1 = 'X', jogador2 = 'O';

    do {
        ImprimirNaTela();
        if (jogador == 1) {
            LerCoordenadas(jogador1); //Jogador 1
            jogador++;
            vitoriaX = vitoriaX + GanhouPorLinhas(jogador1);
            vitoriaX = vitoriaX + GanhouPorColunas(jogador1);
            vitoriaX = vitoriaX + GanhouPorDiagonalPrincipal(jogador1);
            vitoriaX = vitoriaX + GanhouPorDiagonalSecundaria(jogador1);
        } else {
            FazerMovimentoMaquina(jogador2); // Jogador 2 (computador)
            jogador = 1;
            vitoriaO = vitoriaO + GanhouPorLinhas(jogador2);
            vitoriaO = vitoriaO + GanhouPorColunas(jogador2);
            vitoriaO = vitoriaO + GanhouPorDiagonalPrincipal(jogador2);
            vitoriaO = vitoriaO + GanhouPorDiagonalSecundaria(jogador2);
        }
    } while (vitoriaX == 0 && vitoriaO == 0 && QuantVazias() > 0);

    ImprimirNaTela();

    // Resultados
    if (vitoriaO == 1) {
        printf("\nParabens jogador 2. Você venceu!!!\n");
        vitoriasJogador2++;
    } else if (vitoriaX == 1) {
        printf("\nParabens jogador 1. Você venceu!!!\n");
        vitoriasJogador1++;
    } else {
        printf("\nEmpate!\n");
    }

}



/* Função principal para jogar no programa, nela iremos coloca-la no arquivo principal e que transportará todo esse conteúdo*/
int JogoContraComputador() {
    int opcao;
    int notaopcar;
    setlocale(LC_ALL, "portuguese"); // Deixa em português

    do {
        InicializarMatriz();
        jogar();

        printf("\n\tDigite [1] para jogar novamente\n\tDigite [2] para ver os resultados atuais[RANKING] + licao de moral final\n\tDigite [3] para ver os creditos\n\tou qualquer outra tecla para sair direto do campeonato: ");  // Pergunta com as 4 opções
        scanf("%d", &opcao);

        if (opcao == 2) {   // Ranking
            ImprimirResultado();
            printf("\n\tLICAO DE MORAL:\n");
            printf("\t'Nao nasci para competir com os outros, mas para superar a mim mesmo!'\n");

        } else if (opcao == 3) { // Créditos
            printf("\n\t\tJogo criado por:\n");
            printf("\t\tJoao Pedro Feitoza Primo\n");
            printf("\t\tValdir Evangelista Coutinho Filho\n");
            printf("\t\tWilliam Henrique Leite Alves Pereira\n");
            printf("\t\tJean Icaro Lima de Oliveira\n");
            printf("\t\tRafael Olivio Ribeiro Campos\n");
        }

    } while (opcao == 1); // Joga novamente

    printf("\nObrigado por jogar!\n"); // Caso nenhuma das opções anteriores foi acionada, então sairá do jogo

    return 0;
}
