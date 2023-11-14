#include <stdio.h>
#include <stdlib.h>

// 2 * 15 = 31
#define TAM 31

int hashFunction (int chave){
    return chave % TAM; // Resto da divisão
}

void initTable (int t[]){ // t = Tabela Hash
    int i;
    for (i = 0; i < TAM; i++)
        t[i] = 0;
}

void insert(int t[], int valor){
    int id = hashFunction(valor);

    while(t[id] != 0){
        id = hashFunction(id + 1);
    }
    t[id] = valor;
}

int search(int t[], int chave){
    int id = hashFunction(chave);
    printf("\nIndice Criado: %d\n", id);

    while(t[id] != 0){
        if(t[id] == chave)
            return t[id];
        else
            id = hashFunction(id + 1);
    }
    return 0;
}

void print(int t[]){
    int i;
    for (i = 0; i < TAM; i++){
        printf("%d = %d\n", i, t[i]);
    }
}

int main(){
    int tabela[TAM];

    initTable(tabela);

    insert(tabela, 235); // 18
    insert(tabela, 196); // 10
        insert(tabela, 196); // 10
            insert(tabela, 196); // 10
                insert(tabela, 196); // 10
    insert(tabela, 23549); // 20
    insert(tabela, 494); // 29
    insert(tabela, 848); // 11
    insert(tabela, 848); // 11

    print(tabela);

    int retorno = search(tabela, 235);
    if(retorno != 0)
        printf("Valor encontrado: %d", retorno);
    else
        printf("Valor não encontrado!\n");
}
