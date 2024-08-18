#include <stdio.h>
#include <windows.h> // Inclui a biblioteca para utilizar a função SetConsoleOutputCP
#include "biblioteca.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int opcao;

    do {
        exibirMenu();
        printf("Selecione a Opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarLivro();
                break;
            case 2:
                consultarLivro();
                break;
            case 3:
                atualizarDisponibilidade();
                break;
            case 4:
                removerLivro();
                break;
            case 5:
                printf("\nObrigado por utilizar o Sistema de Biblioteca!\n");
                getchar();
                break;
            default:
                printf("\nOpção inválida! Por favor, tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
