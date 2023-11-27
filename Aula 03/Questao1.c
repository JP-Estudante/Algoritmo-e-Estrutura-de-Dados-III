#include <stdio.h>
#include <stdlib.h>

struct noArv {
    int info;
    struct noArv* sae;
    struct noArv* sad;
};
typedef struct noArv NoArvore;

NoArvore* arvore_criaVazia(void) {
    return NULL;
}

NoArvore* arvore_Cria(int info, NoArvore* sae, NoArvore* sad) {
    NoArvore* p = (NoArvore*)malloc(sizeof(NoArvore));
    p->info = info;
    p->sae = sae;
    p->sad = sad;
    return p;
}

int arvore_vazia(NoArvore* a)
{
    return a == NULL;
}

NoArvore* arvore_libera(NoArvore* a) {
    if (!arvore_vazia(a))
    {
        arvore_libera(a->sae); /* libera sae */
        arvore_libera(a->sad); /* libera sad */
        free(a);               /* libera raiz */
    }
    return NULL;
}

int nos_folhas(NoArvore* a) {
    if (a == NULL)
        return 0;
    else
    {
        if (a->sae == NULL && a->sad == NULL)
            return 1;
        else
            return nos_folhas(a->sae) + nos_folhas(a->sad);
    }
}

void arvore_imprime(NoArvore* a) {
    if (a != NULL)
    {
        printf("%d ", a->info);
        arvore_imprime(a->sae);
        arvore_imprime(a->sad);
    }
}

int altura_arv(NoArvore* a) {
    if (a == NULL)
        return -1;
    else
    {
        int alt_sae = altura_arv(a->sae);
        int alt_sad = altura_arv(a->sad);

        if (alt_sae < alt_sad)
            return alt_sad + 1;
        else
            return alt_sae + 1;
    }
}

int arvore_alturaMaior(NoArvore* a, int altura) {
    int h = altura_arv(a);

    if (h < altura)
        return 0;
    else
        return 1;
}

int nos_intermediarios(NoArvore* a) {
    if (a == NULL)
        return 0;

    // Se o nó não for folha, incrementa 1 e explora os filhos
    if (a->sae != NULL || a->sad != NULL)
        return 1 + nos_intermediarios(a->sae) + nos_intermediarios(a->sad);

    return 0;
}

int main() {
    int n;
    NoArvore* arvore = arvore_Cria(1,
        arvore_Cria(2,
            arvore_Cria(4, arvore_criaVazia(), arvore_criaVazia()),
            arvore_Cria(5, arvore_criaVazia(), arvore_criaVazia())
        ),
        arvore_Cria(3,
            arvore_criaVazia(),
            arvore_Cria(6, arvore_criaVazia(), arvore_criaVazia())
        )
    );
    printf("Arvore:\n\n");
    arvore_imprime(arvore);
    printf("\n");
    n = nos_folhas(arvore);
    printf("Total Folhas: %d\n", n);

    n = nos_intermediarios(arvore);
    printf("Total Intermediarios: %d\n", n);

    n = arvore_alturaMaior(arvore, 2);
    printf("Altura da arvore eh maior que 2? %s\n", n == 1 ? "Sim" : "Nao");

    return 0;
}