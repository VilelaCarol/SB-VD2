#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// Definição da estrutura Livro
typedef struct {
    int idLivro;                // Identificador único do livro
    char titulo[100];           // Título do livro
    char autor[50];             // Nome do autor do livro
    int anoPublicacao;          // Ano de publicação do livro
    int disponivel;             // Status de disponibilidade (1 = disponível, 0 = emprestado)
} Livro;

// Declaração das funções
void adicionarLivro();
void consultarLivro();
void atualizarDisponibilidade();
void removerLivro();
void exibirMenu();

#endif 
