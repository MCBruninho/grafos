#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "busca_profundidade.h"

Pilha *criar_pilha(int capacidade) {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->dados = (int *)malloc(sizeof(int) * capacidade);
    p->capacidade = capacidade;
    p->topo = -1;
    return p;
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, int v) {
    if (p->topo == p->capacidade - 1) return; /* pilha cheia */
    p->topo++;
    p->dados[p->topo] = v;
}

int desempilhar(Pilha *p) {
    if (pilha_vazia(p)) return -1;
    int v = p->dados[p->topo];
    p->topo--;
    return v;
}

void liberar_pilha(Pilha *p) {
    free(p->dados);
    free(p);
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred, int *ordem, int *n_ordem) {
    visitado[u] = 1;
    ordem[*n_ordem] = u;
    (*n_ordem)++;
    printf("Empilhar %d\n", u + 1);

    for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
        int v = no->vertice;
        if (!visitado[v]) {
            pred[v] = u;
            dfs_recursiva(g, v, visitado, pred, ordem, n_ordem);
        }
    }

    printf("Desempilhar %d\n", u + 1);
}

void dfs_iterativa(GrafoLista *g, int origem, int *visitado, int *pred, int *ordem, int *n_ordem) {
    /* a capacidade e o numero de arestas no pior caso; n vertices bastam
       porque so empilhamos vizinhos ainda nao visitados de cada vertice */
    Pilha *p = criar_pilha(g->num_vertices * g->num_vertices + 1);

    empilhar(p, origem);

    while (!pilha_vazia(p)) {
        int u = desempilhar(p);
        if (visitado[u]) continue;   /* ja foi descoberto por outro caminho */

        visitado[u] = 1;
        ordem[*n_ordem] = u;
        (*n_ordem)++;
        printf("Visita %d\n", u + 1);

        for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
            int v = no->vertice;
            if (!visitado[v]) {
                pred[v] = u;
                empilhar(p, v);
            }
        }
    }

    liberar_pilha(p);
}

/* Visita em profundidade guardando o pai: se encontrarmos um vizinho ja
   visitado que nao seja o pai, fechamos um ciclo. */
static int busca_ciclo(GrafoLista *g, int u, int pai, int *visitado) {
    visitado[u] = 1;

    for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
        int v = no->vertice;
        if (!visitado[v]) {
            if (busca_ciclo(g, v, u, visitado)) return 1;
        } else if (v != pai) {
            printf("Ciclo detectado na aresta {%d, %d}\n", u + 1, v + 1);
            return 1;
        }
    }

    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int n = g->num_vertices;
    int *visitado = (int *)calloc(n, sizeof(int));
    int ciclo = 0;

    for (int i = 0; i < n && !ciclo; i++) {
        if (!visitado[i]) ciclo = busca_ciclo(g, i, -1, visitado);
    }

    free(visitado);
    return ciclo;
}
