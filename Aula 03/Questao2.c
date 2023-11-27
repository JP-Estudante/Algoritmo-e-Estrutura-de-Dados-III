#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Aluno {
    int matricula;
    char* nome;
    float media;
};
typedef struct Aluno aluno;

struct NoABB {
    aluno* info;
    struct NoABB* esq;
    struct NoABB* dir;
};
typedef struct NoABB noABB;

noABB* abb_insere(noABB* a, int mat, char* nome, float media) {
    if (a == NULL) {
        aluno* newAluno = (aluno*)malloc(sizeof(aluno));
        newAluno->matricula = mat;
        newAluno->nome = nome; // strdup - criar uma cópia do nome
        newAluno->media = media;

        noABB* newABB = (noABB*)malloc(sizeof(noABB));
        newABB->info = newAluno;
        newABB->esq = NULL;
        newABB->dir = NULL;

        return newABB;
    }

    if (media <= a->info->media)
        a->esq = abb_insere(a->esq, mat, nome, media);
    else
        a->dir = abb_insere(a->dir, mat, nome, media);

    return a;
}

void abb_imprime(noABB* a) {
    if (a != NULL) {
        printf("Matricula: %d \nNome: %s \nMedia %.2f\n\n", a->info->matricula, a->info->nome, a->info->media);
        abb_imprime(a->dir);
    }
}

int arv_vazia(noABB* a) {
    return a == NULL;
}

void abb_libera(noABB* a) {
    if (!arv_vazia(a)) {
        abb_libera(a->esq);
        abb_libera(a->dir);
        free(a->info->nome);
        free(a->info);
        free(a);
    }
}

void abb_alunoComMaiorMedia(noABB* a) {
    if (a == NULL)
        return; // Árvore vazia

    if (a->dir == NULL) {
        printf("Matricula: %d \nNome: %s \nMedia %.2f\n\n", a->info->matricula, a->info->nome, a->info->media);
        return;
    }

    abb_alunoComMaiorMedia(a->dir);
}

int abb_contaAprovados(noABB* a) {
    if (a == NULL)
        return 0; // Árvore vazia

    int contagemEsq = abb_contaAprovados(a->esq);
    int contagemDir = abb_contaAprovados(a->dir);

    if (a->info->media >= 5)
        return contagemDir + contagemEsq + 1; // Conta o nó atual

    else
        return contagemDir + contagemEsq; // Não conta o nó atual, pois não foi aprovado
}

void abb_imprimeAprovados(noABB* a) {
    if (a == NULL)
        return; // Árvore vazia

    abb_imprimeAprovados(a->dir); // Imprime aprovados da subárvore direita

    if (a->info->media >= 5.0) {
        printf("Matricula: %d \nNome: %s \nMedia %.2f\n\n", a->info->matricula, a->info->nome, a->info->media);
    }

    abb_imprimeAprovados(a->esq); // Imprime aprovados da subárvore esquerda
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    noABB* abb = NULL;
    abb = abb_insere(abb, 456124, "Pedro Duarte", 7.5);
    abb = abb_insere(abb, 453984, "Ana Silva", 8.8);
    abb = abb_insere(abb, 365597, "Joao Filho", 2.5);
    abb = abb_insere(abb, 687451, "Maria Gomes", 10.0);
    abb = abb_insere(abb, 364512, "Silvio Lins", 4.8);
    abb = abb_insere(abb, 984544, "Marcia Morais", 7.8);
    abb = abb_insere(abb, 698421, "Bruno Rodrigues", 2.0);
    abb = abb_insere(abb, 784512, "Thais Silva", 6.5);
    abb = abb_insere(abb, 694231, "Ricardo Costa", 9.5);
    abb = abb_insere(abb, 126411, "Julia Neves", 8.0);

    printf("Alunos em ordem crescente de media:\n");
    abb_imprime(abb);

    printf("Aluno com maior media:\n");
    abb_alunoComMaiorMedia(abb);

    printf("Numero de alunos aprovados: %d", abb_contaAprovados(abb));

    printf("\n\nAlunos aprovados em ordem decrescente: \n");
    abb_imprimeAprovados(abb);

    return 0;
}