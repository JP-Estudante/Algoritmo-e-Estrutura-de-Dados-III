#include<stdio.h>
#include<stdlib.h>

struct noArv
{
    int info;
    struct noArv *esq;
    struct noArv *dir;
};
typedef struct noArv NoArv;

NoArv* cria_arv_vazia(void){
    return NULL;
}

NoArv* cria_arvore(int v, NoArv *e, NoArv *d)
{
    NoArv *p= (NoArv *)malloc(sizeof(NoArv));
    p->info = v;
    p->esq = e;
    p->dir = d;
    return p;
}

int arv_vazia (NoArv* a)
{
    return a==NULL;
}

NoArv* arv_libera (NoArv* a)
{
    if (!arv_vazia(a)){
        arv_libera(a->esq); /* libera sae */
        arv_libera(a->dir); /* libera sad */
        free(a); /* libera raiz */
    }
    return NULL;
}
void imprime_arv(NoArv *a)
{
    if (a != NULL)
    {
        printf("%d ",a->info);
        imprime_arv(a->esq);
        imprime_arv(a->dir);
    }
}

void imprime_arv_simetrica(NoArv *a)
{
    if (a!=NULL)
    {
        imprime_arv_simetrica(a->esq);
        printf("%d ",a->info);
        imprime_arv_simetrica(a->dir);
    }
}

NoArv* busca_arv(NoArv *a, int v)
{
    if (a == NULL)
        return NULL;
    if (a->info > v)
        return busca_arv(a->esq, v);
    if (a->info < v)
        return busca_arv(a->dir, v);

    return a;
}

NoArv* insere_arv(NoArv *a, int v)
{
    if (busca_arv(a, v) != NULL)
        return a;

    if (a == NULL)
    {
        a = (NoArv *)malloc(sizeof(NoArv));
        a->info = v;
        a->esq = a->dir = NULL;
    }
    else
        if (v < a->info)
             a->esq = insere_arv(a->esq, v);
        else // v >= a->info //n?o permite inserir nodos iguais
            a->dir = insere_arv(a->dir, v);

    return a;
}

NoArv* retira_arv(NoArv* r, int v)
{
    NoArv *t, *f;

    if (r == NULL)
        return NULL;
    else
        if (r->info > v)
            r->esq = retira_arv(r->esq, v);
        else
            if (r->info < v)
                r->dir = retira_arv(r->dir, v);
            else /* achou o n? a remover */
            {
                if (r->esq == NULL && r->dir == NULL) /* n? sem filhos */
                {
                    free(r);
                    r = NULL;
                }
                else
                    if (r->esq == NULL) /* n? s? tem filho ? direita */
                    {
                        t = r;
                        r = r->dir;
                        free(t);
                    }
                    else
                        if (r->dir == NULL) /* s? tem filho ? esquerda */
                        {
                            t = r;
                            r = r->esq;
                            free (t);
                        }
                        else /* n? tem os dois filhos */
                        {
                            f = r->esq;
                            while (f->dir != NULL)
                            {
                                f = f->dir;
                            }
                            r->info = f->info; /* troca as informa??es */
                            f->info = v;
                            r->esq = retira_arv(r->esq, v);
                        }
            }
    return r;
}

int main (void)
{
    //NoArv *a = cria_arv_vazia();
    NoArv *a = cria_arvore(5,cria_arvore(3,NULL,cria_arvore(4,NULL,NULL)),
               cria_arvore(9,cria_arvore(7,NULL,NULL),cria_arvore(11,NULL,NULL)));

    a = insere_arv(a, 8);
    a = insere_arv(a, 2);
    a = insere_arv(a, 5);
    a = insere_arv(a, 10);
    a = insere_arv(a, 32);

    //int teste;
    //scanf("%i", &teste);

    imprime_arv(a);

    a = retira_arv(a, 8);

    printf("\n\nArvore vazia? %s\n", arv_vazia(a) == 1 ? "Sim" : "Nao");

    imprime_arv(a);

    NoArv *t = busca_arv(a, 9);
    if (t != NULL)
        printf("\nValor %d encontrado\n", t->info);

    return 0;
}
