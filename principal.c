#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "function_dois-jogadores.h"
#include "function_computador.h"
#include <locale.h>
// Aqui tem que ter todas as bibliotecas possíveis utilizadas no mesmo arquivo



// Função do modo de jogar
int QuerJogarComo() {
    int Escolha;
    char buffer[100]; // buffer para armazenar a entrada do usuário


    printf("_______________________________________________________________________________________\n");
    printf("|                                                                                     |\n");
    printf("|  sssssssss d   sSSs.      sss sssss d s.     sSSs.      sss sssss   sSSSs   d sss   |\n");
    printf("|      S     S  S               S     S  ~O   S               S      S     S  S       |\n");
    printf("|      S     S S                S     S   `b S                S     S       S S       |\n");
    printf("|      S     S S                S     S sSSO S                S     S       S S sSSs  |\n");
    printf("|      S     S S                S     S    O S                S     S       S S       |\n");
    printf("|      S     S  S               S     S    O  S               S      S     S  S       |\n");
    printf("|      P     P   sss            P     P    P   sss            P        sss    P sSSss |\n");
    printf("_______________________________________________________________________________________\n");


    printf("\n\nSeja bem-vindo ao jogo da velha! \n");
    
    /* Aqui fizemos uma pergunta no "do while" para fazer a pergunta inicialmente e se a resposta do usuário não for a ideal, a pergunta se repete*/
    do {
        printf("Escolha o seu modo de jogar, digite o numero correspondente à sua pretensao!\n"); //Menu
        printf("[1] = Contra o computador\t\t[2] = Dois jogadores\n\n");
        printf("ESCOLHA: ");

        if (scanf("%i", &Escolha) != 1) {
            // Se a entrada não for um número inteiro, limpa o buffer e exibe uma mensagem de erro
            scanf("%s", buffer);
            printf("Opção Invalida! Digite apenas números inteiros.\n");
            Escolha = 0; // Define Escolha como 0 para que o loop continue
        } else {
            if (Escolha == 1) {
                printf("Voce escolheu jogar contra o computador.\n");
            } else if (Escolha == 2) {
                printf("Voce escolheu jogar com dois jogadores.\n");
            } else {
                printf("Opcao Inválida! Digite novamente!\n");
            }
        }
    } while (Escolha != 1 && Escolha != 2);

    return Escolha; // Retorna a escolha do usuário
}

int main() {
    setlocale(LC_ALL, "portuguese"); // Coloca em português
    int escolha = QuerJogarComo(); // A variável "escolha" recebe a opção que o jogador escolheu anteriormente

    if (escolha == 1) {
        printf("Vamos jogar contra o computador\n");
        JogoContraComputador(); // Conteúdo de jogar contra o computador
    } else if (escolha == 2) {
        printf("Vamos jogar contra dois jogadores\n");
        JogoContraDois();   // Conteúdo de jogar contra outro usuário
    } else {
        printf("\n");
    }

    return 0;
}