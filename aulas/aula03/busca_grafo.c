#include "grafo_lista.h"
#include "busca_grafo.h"
#include <stdio.h>

int topo = 0;

void dfs(GrafoLista *g, int u, int *visitado) {
    visitado[u] = 1;
    No *no = g->lista[u];
    while (no != NULL) {
        int v = no->vertice;
        if (!visitado[v]) dfs(g, v, visitado);
        no = no->proximo;
    }
    printf("Desempilhar %i\n", u+1);
}