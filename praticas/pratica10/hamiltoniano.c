#include "hamiltoniano.h"

#include <stdlib.h>

/* ------------------------------------------------------------------ */
/* Operacoes basicas do grafo                                          */
/* ------------------------------------------------------------------ */

Grafo *grafo_criar(int num_vertices) {
    if (num_vertices < 0) {
        return NULL;
    }

    Grafo *g = malloc(sizeof(Grafo));
    if (g == NULL) {
        return NULL;
    }

    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    g->adj = calloc((size_t)num_vertices, sizeof(int *));

    if (num_vertices > 0 && g->adj == NULL) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < num_vertices; i++) {
        g->adj[i] = calloc((size_t)num_vertices, sizeof(int));

        if (g->adj[i] == NULL) {
            grafo_destruir(g);
            return NULL;
        }
    }

    return g;
}

void grafo_adicionar_aresta(Grafo *g, int u, int v) {
    if (g == NULL ||
        u < 0 || u >= g->num_vertices ||
        v < 0 || v >= g->num_vertices ||
        u == v || g->adj[u][v]) {
        return;
    }

    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
    g->num_arestas++;
}

void grafo_destruir(Grafo *g) {
    if (g == NULL) {
        return;
    }

    if (g->adj != NULL) {
        for (int i = 0; i < g->num_vertices; i++) {
            free(g->adj[i]);
        }
    }

    free(g->adj);
    free(g);
}

/* Gerador congruencial linear simples, para resultados reprodutiveis. */
static unsigned proximo_aleatorio(unsigned *estado) {
    *estado = *estado * 1103515245u + 12345u;
    return (*estado >> 16) & 0x7FFFu;
}

Grafo *grafo_aleatorio(int num_vertices, double probabilidade, unsigned semente) {
    Grafo *g = grafo_criar(num_vertices);
    if (g == NULL) {
        return NULL;
    }

    unsigned estado = semente;

    for (int u = 0; u < num_vertices; u++) {
        for (int v = u + 1; v < num_vertices; v++) {
            double r = (double)proximo_aleatorio(&estado) / 32768.0;

            if (r < probabilidade) {
                grafo_adicionar_aresta(g, u, v);
            }
        }
    }

    return g;
}

/* ------------------------------------------------------------------ */
/* Backtracking                                                        */
/* ------------------------------------------------------------------ */

/*
 * Tenta completar 'caminho' a partir da posicao 'pos'.
 * Se 'fechar_ciclo' for 1, o ultimo vertice precisa ser vizinho de caminho[0].
 */
static int bt_recursivo(
    const Grafo *g,
    int *caminho,
    int *visitado,
    int pos,
    int fechar_ciclo
) {
    int n = g->num_vertices;

    if (pos == n) {
        return !fechar_ciclo || g->adj[caminho[n - 1]][caminho[0]];
    }

    int ultimo = caminho[pos - 1];

    for (int v = 0; v < n; v++) {
        if (!visitado[v] && g->adj[ultimo][v]) {
            visitado[v] = 1;
            caminho[pos] = v;

            if (bt_recursivo(g, caminho, visitado, pos + 1, fechar_ciclo)) {
                return 1;
            }

            visitado[v] = 0; /* desfaz a escolha */
        }
    }

    return 0;
}

static int buscar(const Grafo *g, int *caminho, int fechar_ciclo) {
    if (g == NULL || caminho == NULL) {
        return 0;
    }

    int n = g->num_vertices;

    if (n == 0) {
        return 0;
    }

    int *visitado = calloc((size_t)n, sizeof(int));
    if (visitado == NULL) {
        return 0;
    }

    /* No ciclo basta comecar em 0; no caminho testamos todos os inicios. */
    int inicios = fechar_ciclo ? 1 : n;
    int achou = 0;

    for (int s = 0; s < inicios && !achou; s++) {
        visitado[s] = 1;
        caminho[0] = s;
        achou = bt_recursivo(g, caminho, visitado, 1, fechar_ciclo);
        visitado[s] = 0;
    }

    free(visitado);

    return achou;
}

int encontrar_caminho_hamiltoniano_bt(const Grafo *g, int *caminho) {
    return buscar(g, caminho, 0);
}

int encontrar_ciclo_hamiltoniano_bt(const Grafo *g, int *ciclo) {
    return buscar(g, ciclo, 1);
}
