#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista* criar_grafo_lista(int n) {
    GrafoLista *g = malloc(sizeof(GrafoLista));
    g->n = n;
    g->adj = calloc(n, sizeof(No *));
    return g;
}

static int valido(GrafoLista *g, int v) {
    return v >= 0 && v < g->n;
}

static void inserir_no(GrafoLista *g, int origem, int destino) {
    No *novo = malloc(sizeof(No));
    novo->destino = destino;
    novo->prox = g->adj[origem];
    g->adj[origem] = novo;
}

static void remover_no(GrafoLista *g, int origem, int destino) {
    No **atual = &g->adj[origem];
    while (*atual && (*atual)->destino != destino) atual = &(*atual)->prox;
    if (*atual) {
        No *tmp = *atual;
        *atual = tmp->prox;
        free(tmp);
    }
}

void inserir_aresta_lista(GrafoLista* g, int u, int v) {
    if (!valido(g, u) || !valido(g, v)) return;
    inserir_no(g, u, v);
    inserir_no(g, v, u);
}

void remover_aresta_lista(GrafoLista* g, int u, int v) {
    if (!valido(g, u) || !valido(g, v)) return;
    remover_no(g, u, v);
    remover_no(g, v, u);
}

int grau_lista(GrafoLista* g, int v) {
    if (!valido(g, v)) return -1;
    int grau = 0;
    for (No *atual = g->adj[v]; atual; atual = atual->prox) grau++;
    return grau;
}

int sao_adjacentes_lista(GrafoLista* g, int u, int v) {
    if (!valido(g, u) || !valido(g, v)) return 0;
    for (No *atual = g->adj[u]; atual; atual = atual->prox)
        if (atual->destino == v) return 1;
    return 0;
}

void imprimir_grafo_lista(GrafoLista* g) {
    for (int i = 0; i < g->n; i++) {
        printf("%2d:", i);
        for (No *atual = g->adj[i]; atual; atual = atual->prox) printf(" -> %d", atual->destino);
        printf("\n");
    }
}

void liberar_grafo_lista(GrafoLista* g) {
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];
        while (atual) {
            No *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}