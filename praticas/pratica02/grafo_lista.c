#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo(int n) {
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->lista = (No **)malloc(sizeof(No *) * n);
    for (int i = 0; i < n; i++)
    {
        g->lista[i] = NULL;
    }
    return g;
}

/* Insere v na lista de adjacencia de u (aresta direcionada u -> v). */
void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *proximo = g->lista[u];
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->proximo = proximo;
    g->lista[u] = no;
}

/* Aresta {u, v} de um grafo nao direcionado: entra nas duas listas. */
void adicionar_aresta_nao_direcionada(GrafoLista *g, int u, int v) {
    adicionar_aresta(g, u, v);
    adicionar_aresta(g, v, u);
}

void imprimir_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("%d: -> ", i + 1);
        No *no = g->lista[i];
        while (no != NULL) {
            printf("%d -> ", no->vertice + 1);
            no = no->proximo;
        }
        printf("NULL\n");
    }
}

void liberar_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No *no = g->lista[i];
        while (no != NULL) {
            No *proximo = no->proximo;
            free(no);
            no = proximo;
        }
    }
    free(g->lista);
    free(g);
}
