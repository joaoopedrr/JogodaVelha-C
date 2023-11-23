#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>


// Aqui eu defino uma estrutura para a matriz do jogo
typedef struct {
    char jogoz[3][3];
} Matriz;



// Variáveis para contar as vitórias dos jogadores
int vitoriasJogador1z = 0;
int vitoriasJogador2z = 0;



// Função para inicializar a matriz 
void InicializarMatriz87(Matriz *m) {
    for (int li = 0; li < 3; li++) {
        for (int co = 0; co < 3; co++)
            m->jogoz[li][co] = ' ';
    }
}



// Aqui é uma função para imprimir o tabuleiro do jogo na tela
void ImprimirNaTela87(Matriz *m) {
    printf("\n\n\t 0   1   2\n\n");
    for (int li = 0; li < 3; li++) {
        for (int co = 0; co < 3; co++) {
            if (co == 0)
                printf("\t");
            printf(" %c ", m->jogoz[li][co]);
            if (co < 2)
                printf("|");
            if (co == 2)
                printf("   %d", li);
        }
        printf("\n");
        if (li < 2)
            printf("\t-----------\n");
    }
}






// Função para verificar se um jogador ganhou em uma linha específica
int GanhouPorLinha87(Matriz *m, int linhata, char jogadore) {
    return (m->jogoz[linhata][0] == jogadore && m->jogoz[linhata][1] == jogadore && m->jogoz[linhata][2] == jogadore);
}




// Função para verificar se um jogador ganhou em qualquer linha
int GanhouPorLinhas87(Matriz *m, char jogadore) {
    int ganhoulo = 0;
    for (int li = 0; li < 3; li++)
        ganhoulo = ganhoulo + GanhouPorLinha87(m, li, jogadore);
    return ganhoulo;
}




// Função para verificar se um jogador ganhou em uma coluna específica
int GanhouPorColuna87(Matriz *m, int colunata, char jogadore) {
    return (m->jogoz[0][colunata] == jogadore && m->jogoz[1][colunata] == jogadore && m->jogoz[2][colunata] == jogadore);
}




// Função para verificar se um jogador ganhou em qualquer coluna
int GanhouPorColunas87(Matriz *m, char jogadore) {
    int ganhoulo = 0;
    for (int li = 0; li < 3; li++)
        ganhoulo = ganhoulo + GanhouPorColuna87(m, li, jogadore);
    return ganhoulo;
}




// Função para verificar se um jogador ganhou na diagonal principal
int GanhouPorDiagonalPrincipal87(Matriz *m, char jogadore) {
    return (m->jogoz[0][0] == jogadore && m->jogoz[1][1] == jogadore && m->jogoz[2][2] == jogadore);
}




// Função para verificar se um jogador ganhou na diagonal secundária
int GanhouPorDiagonalSecundaria87(Matriz *m, char jogadore) {
    return (m->jogoz[0][2] == jogadore && m->jogoz[1][1] == jogadore && m->jogoz[2][0] == jogadore);
}




// Função para verificar se uma posição é válida na matriz
int ehValida87(Matriz *m, int linhata, int colunata) {
    return (linhata >= 0 && linhata < 3 && colunata >= 0 && colunata < 3 && m->jogoz[linhata][colunata] == ' ');
}






// Função para verificar se a entrada é numérica, para não acontecer problemas com strings
int verificaNumero87(const char *input) {
    while (*input) {
        if (!isdigit(*input)) {
            return 0; // Retorna 0 se encontrar algum caractere que não é número
        }
        input++;
    }
    return 1; // Retorna 1 se todos os caracteres são números
}



// Aqui eu leio as coordenadas do jogador
void LerCoordenadas87(Matriz *m, char jogadore) {
    int linhaz, colunaz;
    char input[20]; // Aqui eu defino um tamanho suficiente para armazenar os números digitados como strings

    printf("Jogador %c, digite linha e coluna (numeros de 0 a 2 cada): ", jogadore);

    // Enquanto a entrada não for numérica, continue pedindo ao usuário para digitar novamente(pra não dar bug)
    do {
        scanf("%s", input);
        if (!verificaNumero87(input)) {
            printf("Entrada invalida! Digite apenas numeros (0 a 2 cada): ");
        } else {
            linhaz = atoi(input); //Converter a string para inteiro, para aceitar corretamente caso o erre
            scanf("%s", input);
            if (!verificaNumero87(input)) {
                printf("Entrada invalida! Digite apenas numeros (0 a 2 cada): ");
            } else {
                colunaz = atoi(input); // Converter a string para inteiro
            }
        }
    } while (!verificaNumero87(input));

// Verificar se os números estão no intervalo correto de (0 a 2), pois é as possibilidades no jogo da velha
    while (!ehValida87(m, linhaz, colunaz)) {
        printf("Posicao invalida! Digite outra linha e coluna (numeros de 0 a 2 cada): ");
        scanf("%d%d", &linhaz, &colunaz);
    }
    // Ver e faz o que precisar com os números válidos
    m->jogoz[linhaz][colunaz] = jogadore;
}






// Função que conta a quantidade de posições vazias no tabuleiro
int QuantVazias87(Matriz *m) {
    int quantidadez = 0;
    for (int li = 0; li < 3; li++) {
        for (int co = 0; co < 3; co++)
            if (m->jogoz[li][co] == ' ')
                quantidadez++;
    }
    return quantidadez;
}





// Imprime o resultado do jogo
void ImprimirResultado87() {
    printf("\nNumero de vitorias do Jogador 1: %d\n", vitoriasJogador1z);
    printf("Numero de vitorias do Jogador 2: %d\n", vitoriasJogador2z);
}







// Função de jogar, nela será armazenada as jogadas e vitórias das jogadas
void jogar87() {
    Matriz jogoz; // Começa
    InicializarMatriz87(&jogoz);

    int jogadore = 1, vitoriafX = 0, vitoriafO = 0;
    char jogadore1 = 'X', jogadore2 = 'O';

    do {
        ImprimirNaTela87(&jogoz); // Função de colocar na tela a matriz
        LerCoordenadas87(&jogoz, (jogadore == 1) ? jogadore1 : jogadore2); //Jogador 1 e 2

        if (jogadore == 1) {  //Jogador 1
            vitoriafX = GanhouPorLinhas87(&jogoz, jogadore1) || GanhouPorColunas87(&jogoz, jogadore1) ||
                       GanhouPorDiagonalPrincipal87(&jogoz, jogadore1) || GanhouPorDiagonalSecundaria87(&jogoz, jogadore1);
        } else {              //Jogador 2
            vitoriafO = GanhouPorLinhas87(&jogoz, jogadore2) || GanhouPorColunas87(&jogoz, jogadore2) ||
                       GanhouPorDiagonalPrincipal87(&jogoz, jogadore2) || GanhouPorDiagonalSecundaria87(&jogoz, jogadore2);
        }

        jogadore = (jogadore == 1) ? 2 : 1;
    } while (vitoriafX == 0 && vitoriafO == 0 && QuantVazias87(&jogoz) > 0); // Continua o jogo

    ImprimirNaTela87(&jogoz);

    // Resultados
    if (vitoriafO == 1) {
        printf("\nParabens jogador 2. Você venceu!!!\n");
        vitoriasJogador2z++;
    } else if (vitoriafX == 1) {
        printf("\nParabens jogador 1. Você venceu!!!\n");
        vitoriasJogador1z++;
    } else {
        printf("\nEmpate!\n");
    }

    ImprimirResultado87();  // Imprime ele pro usuário
}







/* Função principal para jogar no programa, nela iremos coloca-la no arquivo principal e que transportará todo esse conteúdo*/
int JogoContraDois(){
    int opcao31;
    int notaopcarty;
    setlocale(LC_ALL, "portuguese"); // Deixa em português


    do {
    	Matriz jogoz;
        InicializarMatriz87(&jogoz);
        jogar87();

        printf("\n\tDigite [1] para jogar novamente\n\tDigite [2] para ver os resultados atuais[RANKING] + licao de moral final\n\tDigite [3] para ver os creditos\n\tou qualquer outra tecla para sair direto do campeonato: ");   // Pergunta com as 4 opções
        scanf("%d", &opcao31);

        if (opcao31 == 2) {     // Ranking
            ImprimirResultado87();
            printf("\n\tLICAO DE MORAL:\n");
            printf("\t'Nao nasci para competir com os outros, mas para superar a mim mesmo!'\n");

        } else if (opcao31 == 3) {    // Créditos
            printf("\n\t\tJogo criado por:\n");
            printf("\t\tJoao Pedro Feitoza Primo\n");
            printf("\t\tValdir Evangelista Coutinho Filho\n");
            printf("\t\tWilliam Henrique Leite Alves Pereira\n");
            printf("\t\tJean Icaro Lima de Oliveira\n");
            printf("\t\tRafael Olivio Ribeiro Campos\n");
        }

    } while (opcao31 == 1);    // Joga novamente

    if (opcao31 != 1) {
        printf("\nObrigado por jogar, estamos aqui para sempre continuar com o jogo!\n"); // Saída do jogo
    }
    if (opcao31 != 1 && opcao31 != 2 && opcao31 != 3){
    	printf("Jogo da velha e sensacional, que o jogue para sempre!"); // Agradecimento pós partida
	}
    return 0;
}
