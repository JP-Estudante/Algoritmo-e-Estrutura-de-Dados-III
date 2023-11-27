#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Estrutura para a Árvore de Busca Binária (ABB)
struct noArvABB
{
    int info;
    struct noArvABB* esq;
    struct noArvABB* dir;
};
typedef struct noArvABB NoArvABB;

// Estrutura para a Árvore AVL
struct noArvAVL
{
    int info;
    int bal;   /* hdir - hesq */
    struct noArvAVL* esq;
    struct noArvAVL* dir;
};
typedef struct noArvAVL NoArvAVL;

// Funções para a Árvore de Busca Binária (ABB)

NoArvABB* cria_arv_vazia_abb(void) {
    return NULL;
}

NoArvABB* cria_arvore_abb(int v, NoArvABB* e, NoArvABB* d)
{
    NoArvABB* p = (NoArvABB*)malloc(sizeof(NoArvABB));
    p->info = v;
    p->esq = e;
    p->dir = d;
    return p;
}

int arv_vazia_abb(NoArvABB* a)
{
    return a == NULL;
}

NoArvABB* arv_libera_abb(NoArvABB* a)
{
    if (!arv_vazia_abb(a)) {
        arv_libera_abb(a->esq); /* libera sae */
        arv_libera_abb(a->dir); /* libera sad */
        free(a); /* libera raiz */
    }
    return NULL;
}

void imprime_arv_abb(NoArvABB* a)
{
    if (a != NULL)
    {
        printf("%d ", a->info);
        imprime_arv_abb(a->esq);
        imprime_arv_abb(a->dir);
    }
}

NoArvABB* busca_arv_abb(NoArvABB* a, int v, int* iteracao)
{
    if (a == NULL)
        return NULL;
    (*iteracao)++;
    if (a->info > v)
        return busca_arv_abb(a->esq, v, iteracao);
    if (a->info < v)
        return busca_arv_abb(a->dir, v, iteracao);

    return a;
}

NoArvABB* insere_arv_abb(NoArvABB* a, int v, int* iteracao)
{
    if (busca_arv_abb(a, v, iteracao) != NULL)
        return a;

    if (a == NULL)
    {
        a = (NoArvABB*)malloc(sizeof(NoArvABB));
        a->info = v;
        a->esq = a->dir = NULL;
    }
    else if (v < a->info)
        a->esq = insere_arv_abb(a->esq, v, iteracao);
    else // v >= a->info //não permite inserir nodos iguais
        a->dir = insere_arv_abb(a->dir, v, iteracao);

    return a;
}

NoArvABB* retira_arv_abb(NoArvABB* r, int v)
{
    NoArvABB* t, * f;

    if (r == NULL)
        return NULL;
    else if (r->info > v)
        r->esq = retira_arv_abb(r->esq, v);
    else if (r->info < v)
        r->dir = retira_arv_abb(r->dir, v);
    else /* achou o nó a remover */
    {
        if (r->esq == NULL && r->dir == NULL) /* nó sem filhos */
        {
            free(r);
            r = NULL;
        }
        else if (r->esq == NULL) /* nó só tem filho à direita */
        {
            t = r;
            r = r->dir;
            free(t);
        }
        else if (r->dir == NULL) /* só tem filho à esquerda */
        {
            t = r;
            r = r->esq;
            free(t);
        }
        else /* nó tem os dois filhos */
        {
            f = r->esq;
            while (f->dir != NULL)
            {
                f = f->dir;
            }
            r->info = f->info; /* troca as informações */
            f->info = v;
            r->esq = retira_arv_abb(r->esq, v);
        }
    }
    return r;
}

void inserirValoresArquivoABB(NoArvABB** arvore, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int valor, iteracao = 0;
    while (fscanf(arquivo, "%d", &valor) != EOF) {
        *arvore = insere_arv_abb(*arvore, valor, &iteracao);
    }

    fclose(arquivo);
}

// Funções para a Árvore AVL

int altura_avl(NoArvAVL* t) {
    if (t == NULL)
        return 0;
    int hesq = altura_avl(t->esq);
    int hdir = altura_avl(t->dir);
    return hesq > hdir ? hesq + 1 : hdir + 1;
}

NoArvAVL* cria_vazia_avl(void) {
    return NULL;
}

NoArvAVL* cria_avl(int v, NoArvAVL* esq, NoArvAVL* dir) {
    NoArvAVL* n = (NoArvAVL*)malloc(sizeof(NoArvAVL));
    n->info = v;
    n->bal = altura_avl(dir) - altura_avl(esq);
    n->esq = esq;
    n->dir = dir;
    return n;
}

int verifica_AVL(NoArvAVL* t) {
    if (t == NULL)
        return 1;
    return abs(altura_avl(t->dir) - altura_avl(t->esq)) <= 1;
}

void escreve_avl(NoArvAVL* r) {
    if (r != NULL) {
        escreve_avl(r->esq);
        printf("%d(%d) ", r->info, r->bal);
        escreve_avl(r->dir);
    }
}

void escreve_verifica_avl(NoArvAVL* t) {
    if (!verifica_AVL(t))
        printf("Não é AVL!\n");
    escreve_avl(t);
    printf("\n");
}

void LL(NoArvAVL** r) {
    NoArvAVL* b = *r;
    NoArvAVL* a = b->esq;
    b->esq = a->dir;
    a->dir = b;
    a->bal = 0;
    b->bal = 0;
    *r = a;
}

void RR(NoArvAVL** r) {
    NoArvAVL* a = *r;
    NoArvAVL* b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    a->bal = 0;
    b->bal = 0;
    *r = b;
}

void LR(NoArvAVL** r) {
    NoArvAVL* c = *r;
    NoArvAVL* a = c->esq;
    NoArvAVL* b = a->dir;
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;
    switch (b->bal) {
    case -1:
        a->bal = 0;
        c->bal = 1;
        break;
    case 0:
        a->bal = 0;
        c->bal = 0;
        break;
    case 1:
        a->bal = -1;
        c->bal = 0;
        break;
    }
    b->bal = 0;
    *r = b;
}

void RL(NoArvAVL** r) {
    NoArvAVL* a = *r;
    NoArvAVL* c = a->dir;
    NoArvAVL* b = c->esq;
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;
    switch (b->bal) {
    case -1:
        a->bal = 0;
        c->bal = 1;
        break;
    case 0:
        a->bal = 0;
        c->bal = 0;
        break;
    case 1:
        a->bal = -1;
        c->bal = 0;
        break;
    }
    b->bal = 0;
    *r = b;
}

int aux_insere_avl(NoArvAVL** t, int v, int* cresceu) {
    if (*t == NULL) {
        *t = cria_avl(v, NULL, NULL);
        *cresceu = 1;
        return 1;
    }

    if (v == (*t)->info)
        return 0;

    if (v < (*t)->info) {
        if (aux_insere_avl(&(*t)->esq, v, cresceu)) {
            if (*cresceu) {
                switch ((*t)->bal) {
                case -1:
                    if ((*t)->esq->bal == -1)
                        LL(t);
                    else
                        LR(t);
                    *cresceu = 0;
                    break;
                case 0:
                    (*t)->bal = -1;
                    *cresceu = 1;
                    break;
                case 1:
                    (*t)->bal = 0;
                    *cresceu = 0;
                    break;
                }
            }
            return 1;
        }
        else
            return 0;
    }

    if (aux_insere_avl(&(*t)->dir, v, cresceu)) {
        if (*cresceu) {
            switch ((*t)->bal) {
            case -1:
                (*t)->bal = 0;
                *cresceu = 0;
                break;
            case 0:
                (*t)->bal = 1;
                *cresceu = 1;
                break;
            case 1:
                if ((*t)->dir->bal == 1)
                    RR(t);
                else
                    RL(t);
                *cresceu = 0;
                break;
            }
        }
        return 1;
    }
    else
        return 0;
}

int insere_avl(NoArvAVL** t, int v) {
    int cresceu = 0;
    return aux_insere_avl(t, v, &cresceu);
}

NoArvAVL* busca_arv_avl(NoArvAVL* t, int v, int* iteracao) {
    if (t == NULL)
        return NULL;
    (*iteracao)++;
    if (t->info > v)
        return busca_arv_avl(t->esq, v, iteracao);
    if (t->info < v)
        return busca_arv_avl(t->dir, v, iteracao);

    return t;
}

void inserirValoresArquivoAVL(NoArvAVL** arvore, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int valor;
    while (fscanf(arquivo, "%d", &valor) != EOF) {
        insere_avl(arvore, valor);
    }

    fclose(arquivo);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    clock_t startTime, endTime;
    double tempoTotal;

    // ABB
    double cpuTimeABB;
    startTime = clock(); // Inicia o tempo??
    int contagemABB = 0;
    NoArvABB* a_abb = NULL; // Inicializa a árvore ABB como vazia
    inserirValoresArquivoABB(&a_abb, "../valores_aleatorios.txt");
    NoArvABB* resultadoABB = busca_arv_abb(a_abb, 1000000, &contagemABB);
    endTime = clock(); // Finaliza o tempo ??

    cpuTimeABB = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    if (resultadoABB != NULL) {
        printf("[ABB] Valor encontrado.\n");
        printf("[%d : Iterações]\n", contagemABB);
        printf("[%.4f : Segundos]\n", cpuTimeABB);
    }
    else {
        printf("[ABB] Valor não encontrado.\n");
        printf("[%d : Iterações]\n", contagemABB);
        printf("[%.4f : Segundos]\n", cpuTimeABB);
    }

    // AVL
    double cpuTimeAVL;
    startTime = clock(); // Inicia o tempo??
    int contagemAVL = 0;
    NoArvAVL* t_avl = NULL; // Inicializa a árvore AVL como vazia
    inserirValoresArquivoAVL(&t_avl, "../valores_ordenados.txt");
    NoArvAVL* resultadoAVL = busca_arv_avl(t_avl, 1000000, &contagemAVL);
    endTime = clock(); // Finaliza o tempo ??

    cpuTimeAVL = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    if (resultadoAVL != NULL) {
        printf("\n[AVL] Valor encontrado.\n");
        printf("[%d : Iterações]\n", contagemAVL);
        printf("[%.4f : Segundos]\n", cpuTimeAVL);
    }
    else {
        printf("\n[AVL] Valor não encontrado.\n");
        printf("[%d : Iterações]\n", contagemAVL);
        printf("[%.4f : Segundos]\n", cpuTimeAVL);
    }

    printf("\n[Total AVL e ABB]\n");
    printf("[%.4f] Segundos", (tempoTotal = (cpuTimeABB + cpuTimeAVL)));
    return 0;
}