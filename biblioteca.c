#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void exibirMenu() {
    printf("\033[1;36m\nSistema biblioteca UFMT:\033[0m\n"); // Título em ciano
    printf("\033[1;33m1.\033[0m \033[1;32mCadastrar um novo livro na biblioteca\033[0m\n"); // Texto verde com número em amarelo
    printf("\033[1;33m2.\033[0m \033[1;32mConsultar informações do livro\033[0m\n");
    printf("\033[1;33m3.\033[0m \033[1;32mModificar o status de disponibilidade do livro\033[0m\n");
    printf("\033[1;33m4.\033[0m \033[1;32mExcluir o registro de um livro\033[0m\n");
    printf("\033[1;33m5.\033[0m \033[1;31mSair do sistema\033[0m\n"); // Texto vermelho para a opção de sair
}

// Função para adicionar um novo livro ao arquivo binário
void adicionarLivro() {
    Livro novoLivro;
    FILE *arquivo = fopen("biblioteca.bin", "ab");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite o ID do livro: ");
    scanf("%d", &novoLivro.idLivro);
    printf("Digite o título do livro: ");
    getchar(); 
    fgets(novoLivro.titulo, 100, stdin);
    strtok(novoLivro.titulo, "\n"); 
    printf("Digite o autor do livro: ");
    fgets(novoLivro.autor, 50, stdin);
    strtok(novoLivro.autor, "\n"); 
    printf("Digite o ano de publicação: ");
    scanf("%d", &novoLivro.anoPublicacao);
    novoLivro.disponivel = 1; 

    fwrite(&novoLivro, sizeof(Livro), 1, arquivo);
    fclose(arquivo); 

    printf("Livro adicionado com sucesso!\n");
}

// Função para consultar um livro pelo ID
void consultarLivro() {
    int id;
    Livro livro;
    FILE *arquivo = fopen("biblioteca.bin", "rb"); 

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite o ID do livro que deseja consultar: ");
    scanf("%d", &id);

    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        if (livro.idLivro == id) { 
            printf("\nLivro encontrado:\n");
            printf("ID: %d\n", livro.idLivro);
            printf("Título: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Ano de Publicação: %d\n", livro.anoPublicacao);
            printf("Disponível: %s\n", livro.disponivel ? "Sim" : "Não");
            fclose(arquivo);
            return;
        }
    }

    printf("Livro não encontrado.\n");
    fclose(arquivo);
}

// Função para atualizar a disponibilidade de um livro
void atualizarDisponibilidade() {
    int id;
    Livro livro;
    FILE *arquivo = fopen("biblioteca.bin", "r+b");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite o ID do livro que deseja atualizar: ");
    scanf("%d", &id);

    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        if (livro.idLivro == id) {
            livro.disponivel = !livro.disponivel;
            fseek(arquivo, -(long)sizeof(Livro), SEEK_CUR); 
            fwrite(&livro, sizeof(Livro), 1, arquivo);
            printf("Disponibilidade do livro atualizada com sucesso!\n");
            fclose(arquivo);
            return;
        }
    }

    printf("Livro não encontrado.\n");
    fclose(arquivo);
}

// Função para remover um livro pelo ID
void removerLivro() {
    int id;
    Livro livro;
    FILE *arquivo = fopen("biblioteca.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    printf("Digite o ID do livro que deseja remover: ");
    scanf("%d", &id);

    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        if (livro.idLivro != id) {
            fwrite(&livro, sizeof(Livro), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("biblioteca.bin");
    rename("temp.bin", "biblioteca.bin");

    printf("Livro removido com sucesso!\n");
}
