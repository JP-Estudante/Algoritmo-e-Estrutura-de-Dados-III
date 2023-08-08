/* Material adaptado de http://www.inf.puc-rio.br/~inf1620/material.html */
#include <stdio.h>
#include <stdlib.h>

/* define a estrutura da lista */
struct lista
{
    int info;
    struct lista *prox;
};
typedef struct lista Lista;

/* fun??o de cria??o: retorna uma lista vazia */
Lista *lst_cria(void)
{
    return NULL;
}

// /* inser??o no in?cio: retorna a lista atualizada */
Lista *lst_insere(Lista *l, int i)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = l;
    return novo;
}

/* inser??o no in?cio: retorna a lista atualizada */
Lista *lst_insere_ordenada(Lista *l, int v)
{
    if (l != NULL && l->info < v)
    {
        l->prox = lst_insere_ordenada(l->prox, v);
    }
    else
    {
        Lista *novo = (Lista *)malloc(sizeof(Lista));
        novo->info = v;
        novo->prox = l;
        return novo;
    }
    return l;
}

/* fun??o vazia: retorna 1 se vazia ou 0 se n?o vazia */
int lst_vazia(Lista *l)
{
    return (l == NULL);
}

/* fun??o busca: busca um elemento na lista */
Lista *busca(Lista *l, int v)
{
    Lista *p;
    for (p = l; p != NULL; p = p->prox)
    {
        if (p->info == v)
            return p;
    }
    return NULL; /* n?o achou o elemento */
}

// void lst_libera(Lista *l)
// {
//     Lista *p = l;
//     while (p != NULL)
//     {
//         Lista *t = p->prox; /* guarda refer?ncia p/ pr?x. elemento */
//         free(p);            /* libera a mem?ria apontada por p */
//         p = t;              /* faz p apontar para o pr?ximo */
//     }
// }

void lst_libera(Lista *l)
{
    if (l != NULL)
    {
        Lista *t = l->prox; /* guarda refer?ncia p/ pr?x. elemento */
        free(l);            /* libera a mem?ria apontada por p */
        lst_libera(t);
    }
}

/* fun??o imprime: imprime valores dos elementos */
void lst_imprime(Lista *l)
{
    if (!lst_vazia(l))
    {
        /* imprime primeiro elemento */
        printf("info: %d\n", l->info);
        /* imprime sub-lista */
        lst_imprime(l->prox);
    }
}

/* fun??o retira: retira elemento da lista */
Lista *lst_retira(Lista *l, int v)
{
    if (!lst_vazia(l))
    {
        /* verifica se elemento a ser retirado ? o primeiro */
        if (l->info == v)
        {
            Lista *t = l; /* tempor?rio para poder liberar */
            l = l->prox;
            free(t);
        }
        else
        {
            /* retira de sub-lista */
            l->prox = lst_retira(l->prox, v);
        }
    }
    return l;
}

int main(void)
{
    Lista *l; /* declara uma lista n?o inicializada */

    l = lst_cria(); /* cria e inicializa lista como vazia */

    l = lst_insere_ordenada(l, 23); /* insere na lista o elemento 23 */
    l = lst_insere_ordenada(l, 45); /* insere na lista o elemento 45 */
    l = lst_insere_ordenada(l, 8);  /* insere na lista o elemento 8 */
    l = lst_insere_ordenada(l, 10); /* insere na lista o elemento 10 */

    lst_imprime(l); /*  imprime a lista*/

    /* realiza busca de um valor na lista*/
    if (busca(l, 10) != NULL)
        printf("\nValor encontrado!");
    else
        printf("\nValor nao encontrado!");

    l = lst_retira(l, 10); /*retira da lista o elemento 10*/

    printf("\n\n");
    lst_imprime(l); /*  imprime a lista*/

    printf("\n\n");
    return 0;
}