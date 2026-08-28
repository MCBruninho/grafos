#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"

GrafoMatriz* criar_grafo_matriz(int n) {
    GrafoMatriz *g = malloc(sizeof(GrafoMatriz));
    g->n = n;
    g->adj = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) g->adj[i] = calloc(n, sizeof(int));
    return g;
}

static int valido(GrafoMatriz *g, int v) {
    return v >= 0 && v < g->n;
}

void inserir_aresta_matriz(GrafoMatriz* g, int u, int v) {
    if (!valido(g, u) || !valido(g, v)) return;
    g->adj[u][v] = g->adj[v][u] = 1;
}

void remover_aresta_matriz(GrafoMatriz* g, int u, int v) {
    if (!valido(g, u) || !valido(g, v)) return;
    g->adj[u][v] = g->adj[v][u] = 0;
}

int grau_matriz(GrafoMatriz* g, int v) {
    if (!valido(g, v)) return -1;
    int grau = 0;
    for (int i = 0; i < g->n; i++) grau += g->adj[v][i];
    return grau;
}

int sao_adjacentes_matriz(GrafoMatriz* g, int u, int v) {
    return (valido(g, u) && valido(g, v)) ? g->adj[u][v] : 0;
}

void imprimir_grafo_matriz(GrafoMatriz* g) {
    printf("    ");
    for (int j = 0; j < g->n; j++) printf("%3d", j);
    printf("\n    ");
    for (int j = 0; j < g->n; j++) printf("---");
    printf("\n");
    for (int i = 0; i < g->n; i++) {
        printf("%2d |", i);
        for (int j = 0; j < g->n; j++) printf("%3d", g->adj[i][j]);
        printf("\n");
    }
}

void liberar_grafo_matriz(GrafoMatriz* g) {
    for (int i = 0; i < g->n; i++) free(g->adj[i]);
    free(g->adj);
    free(g);
}