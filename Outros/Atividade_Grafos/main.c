#include <stdio.h>
#include <limits.h>
#include <locale.h>

// Número máximo de cidades
#define MAX_CITIES 100

// Função para encontrar o vértice com a distância mínima
int findMinDistance(int dist[], int visited[], int n) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void printMatrix(int graph[MAX_CITIES][MAX_CITIES], int n) {
    printf("\nMatriz de Adjacência:\n");
    // Imprimindo os números dos vértices
    printf("   [");
    for (int i = 0; i < n; i++) {
        printf("  %2d", i + 1);
    }
    printf(" ]\n");

    // Imprimindo a matriz de adjacência
    for (int i = 0; i < n; i++) {
        printf("%2d [ ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%3d ", graph[i][j]);
        }
        printf("]\n");
    }
}

// Imprime o caminho mínimo entre todas as cidades
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    printf(" -> %d", j + 1);
}

// Imprime a solução
void printSolution(int dist[], int parent[], int n, int src) {
    printf("\nMenor Caminho entre Todas as Cidades:\n");
    for (int i = 0; i < n; i++) {
        if (i != src) {
            printf("De %d para %d: %d", src + 1, i + 1, src + 1);
            printPath(parent, i);
            printf(" -> %d (Distância: %d)\n", i + 1, dist[i]);
        }
    }
}

// Implementação do Algoritmo de Dijkstra
void dijkstra(int graph[MAX_CITIES][MAX_CITIES], int src, int n) {
    int dist[MAX_CITIES];
    int parent[MAX_CITIES];
    int visited[MAX_CITIES];

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = findMinDistance(dist, visited, n);
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, parent, n, src);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int n = 18; // Número de cidades

    int graph[MAX_CITIES][MAX_CITIES] = {
        {0, 20, 0, 0, 0, 0, 0, 29, 0, 0, 0, 29, 37, 0, 0, 0, 0, 0},
        {20, 0, 25, 0, 0, 0, 0, 28, 0, 0, 0, 39, 0, 0, 0, 0, 0, 0},
        {0, 25, 0, 25, 0, 0, 0, 30, 0, 0, 0, 0, 54, 0, 0, 0, 0, 0},
        {0, 0, 25, 0, 39, 32, 42, 0, 23, 33, 0, 0, 0, 56, 0, 0, 0, 0},
        {0, 0, 0, 39, 0, 12, 26, 0, 0, 19, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 32, 12, 0, 17, 0, 0, 35, 30, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 42, 26, 17, 0, 0, 0, 0, 38, 0, 0, 0, 0, 0, 0, 0},
        {29, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 25, 22, 0, 0, 0, 0, 0},
        {0, 0, 0, 23, 0, 0, 0, 0, 0, 26, 0, 0, 34, 1, 0, 43, 0, 0},
        {0, 0, 0, 33, 19, 35, 0, 0, 26, 0, 24, 0, 0, 30, 19, 0, 0, 0},
        {0, 0, 0, 0, 0, 30, 38, 0, 0, 24, 0, 0, 0, 0, 26, 0, 0, 36},
        {29, 39, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 27, 0, 0, 43, 0, 0},
        {37, 0, 54, 0, 0, 0, 0, 22, 34, 0, 0, 27, 0, 24, 0, 19, 0, 0},
        {0, 0, 0, 56, 0, 0, 0, 0, 1, 30, 0, 0, 24, 0, 20, 19, 17, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 26, 0, 0, 20, 0, 0, 18, 21},
        {0, 0, 0, 0, 0, 0, 0, 0, 43, 0, 0, 43, 19, 19, 0, 0, 26, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 18, 26, 0, 15},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 0, 0, 0, 21, 0, 15, 0}
    };

    int source; // Cidade de origem para calcular o menor caminho
    printf("Digite a cidade de origem (1 a %d): ", n);
    scanf("%d", &source);

    printMatrix(graph, n);

    dijkstra(graph, source - 1, n);  // Ajusta o índice da cidade de origem

    return 0;
}
