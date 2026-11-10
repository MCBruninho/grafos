#include "tps.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* Operacoes basicas da instancia                                      */
/* ------------------------------------------------------------------ */

InstanciaTSP *tsp_criar(int n) {
    if (n < 0) {
        return NULL;
    }

    InstanciaTSP *t = malloc(sizeof(InstanciaTSP));
    if (t == NULL) {
        return NULL;
    }

    t->n = n;
    t->dist = calloc((size_t)n, sizeof(int *));

    if (n > 0 && t->dist == NULL) {
        free(t);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        t->dist[i] = calloc((size_t)n, sizeof(int));

        if (t->dist[i] == NULL) {
            tsp_destruir(t);
            return NULL;
        }
    }

    return t;
}

void tsp_destruir(InstanciaTSP *t) {
    if (t == NULL) {
        return;
    }

    if (t->dist != NULL) {
        for (int i = 0; i < t->n; i++) {
            free(t->dist[i]);
        }
    }

    free(t->dist);
    free(t);
}

static unsigned proximo_aleatorio(unsigned *estado) {
    *estado = *estado * 1103515245u + 12345u;
    return (*estado >> 16) & 0x7FFFu;
}

InstanciaTSP *tsp_aleatorio(int n, int peso_maximo, unsigned semente) {
    InstanciaTSP *t = tsp_criar(n);
    if (t == NULL || peso_maximo < 1) {
        tsp_destruir(t);
        return NULL;
    }

    unsigned estado = semente;

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            int peso = 1 + (int)(proximo_aleatorio(&estado) % (unsigned)peso_maximo);
            t->dist[u][v] = peso;
            t->dist[v][u] = peso;
        }
    }

    return t;
}

int tsp_custo_rota(const InstanciaTSP *t, const int *rota) {
    if (t == NULL || rota == NULL || t->n == 0) {
        return -1;
    }

    int custo = 0;

    for (int i = 0; i < t->n; i++) {
        custo += t->dist[rota[i]][rota[(i + 1) % t->n]];
    }

    return custo;
}

/* ------------------------------------------------------------------ */
/* Forca bruta: (n-1)! permutacoes                                     */
/* ------------------------------------------------------------------ */

typedef struct {
    const InstanciaTSP *t;
    int *atual;
    int *melhor;
    int melhor_custo;
} EstadoFB;

/*
 * Gera as permutacoes de atual[pos..n-1] por trocas (swap).
 * 'custo' e o custo acumulado de atual[0] ate atual[pos-1].
 */
static void permutar(EstadoFB *e, int pos, int custo) {
    int n = e->t->n;

    if (pos == n) {
        int total = custo + e->t->dist[e->atual[n - 1]][e->atual[0]];

        if (total < e->melhor_custo) {
            e->melhor_custo = total;
            memcpy(e->melhor, e->atual, (size_t)n * sizeof(int));
        }
        return;
    }

    for (int i = pos; i < n; i++) {
        int tmp = e->atual[pos];
        e->atual[pos] = e->atual[i];
        e->atual[i] = tmp;

        permutar(e, pos + 1, custo + e->t->dist[e->atual[pos - 1]][e->atual[pos]]);

        tmp = e->atual[pos];
        e->atual[pos] = e->atual[i];
        e->atual[i] = tmp;
    }
}

int tsp_forca_bruta(const InstanciaTSP *t, int *rota) {
    if (t == NULL || rota == NULL || t->n == 0) {
        return -1;
    }

    int n = t->n;

    EstadoFB e;
    e.t = t;
    e.melhor = rota;
    e.melhor_custo = INT_MAX;
    e.atual = malloc((size_t)n * sizeof(int));

    if (e.atual == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        e.atual[i] = i;
        rota[i] = i;
    }

    /* Origem fixa em atual[0] = 0: permutamos apenas as posicoes 1..n-1. */
    permutar(&e, 1, 0);

    free(e.atual);

    return e.melhor_custo;
}

/* ------------------------------------------------------------------ */
/* Heuristica do vizinho mais proximo                                  */
/* ------------------------------------------------------------------ */

int tsp_vizinho_mais_proximo(const InstanciaTSP *t, int *rota) {
    if (t == NULL || rota == NULL || t->n == 0) {
        return -1;
    }

    int n = t->n;
    int *visitado = calloc((size_t)n, sizeof(int));

    if (visitado == NULL) {
        return -1;
    }

    rota[0] = 0;
    visitado[0] = 1;

    for (int i = 1; i < n; i++) {
        int atual = rota[i - 1];
        int proximo = -1;

        for (int v = 0; v < n; v++) {
            if (!visitado[v] &&
                (proximo == -1 || t->dist[atual][v] < t->dist[atual][proximo])) {
                proximo = v;
            }
        }

        rota[i] = proximo;
        visitado[proximo] = 1;
    }

    free(visitado);

    return tsp_custo_rota(t, rota);
}

/* ------------------------------------------------------------------ */
/* Heuristica de insercao do mais proximo                              */
/* ------------------------------------------------------------------ */

int tsp_insercao(const InstanciaTSP *t, int *rota) {
    if (t == NULL || rota == NULL || t->n == 0) {
        return -1;
    }

    int n = t->n;

    if (n == 1) {
        rota[0] = 0;
        return 0;
    }

    int *no_ciclo = calloc((size_t)n, sizeof(int));
    /* dist_ciclo[v] = menor distancia de v ate alguma cidade do ciclo */
    int *dist_ciclo = malloc((size_t)n * sizeof(int));

    if (no_ciclo == NULL || dist_ciclo == NULL) {
        free(no_ciclo);
        free(dist_ciclo);
        return -1;
    }

    /* Ciclo inicial: 0 e a cidade mais proxima de 0. */
    int inicial = 1;
    for (int v = 2; v < n; v++) {
        if (t->dist[0][v] < t->dist[0][inicial]) {
            inicial = v;
        }
    }

    rota[0] = 0;
    rota[1] = inicial;
    int tamanho = 2;
    no_ciclo[0] = 1;
    no_ciclo[inicial] = 1;

    for (int v = 0; v < n; v++) {
        dist_ciclo[v] = t->dist[v][0] < t->dist[v][inicial]
                            ? t->dist[v][0]
                            : t->dist[v][inicial];
    }

    while (tamanho < n) {
        /* 1. Selecao: cidade fora do ciclo mais proxima do ciclo. */
        int k = -1;
        for (int v = 0; v < n; v++) {
            if (!no_ciclo[v] && (k == -1 || dist_ciclo[v] < dist_ciclo[k])) {
                k = v;
            }
        }

        /* 2. Insercao: entre rota[i] e rota[i+1] com menor acrescimo. */
        int melhor_pos = 0;
        int melhor_acrescimo = INT_MAX;

        for (int i = 0; i < tamanho; i++) {
            int a = rota[i];
            int b = rota[(i + 1) % tamanho];
            int acrescimo = t->dist[a][k] + t->dist[k][b] - t->dist[a][b];

            if (acrescimo < melhor_acrescimo) {
                melhor_acrescimo = acrescimo;
                melhor_pos = i;
            }
        }

        for (int i = tamanho; i > melhor_pos + 1; i--) {
            rota[i] = rota[i - 1];
        }
        rota[melhor_pos + 1] = k;
        tamanho++;
        no_ciclo[k] = 1;

        for (int v = 0; v < n; v++) {
            if (t->dist[v][k] < dist_ciclo[v]) {
                dist_ciclo[v] = t->dist[v][k];
            }
        }
    }

    free(no_ciclo);
    free(dist_ciclo);

    return tsp_custo_rota(t, rota);
}

/* ------------------------------------------------------------------ */
/* Reducao Ciclo Hamiltoniano -> TSP                                   */
/* ------------------------------------------------------------------ */

InstanciaTSP *grafo_para_tsp(const Grafo *g) {
    if (g == NULL) {
        return NULL;
    }

    InstanciaTSP *t = tsp_criar(g->num_vertices);
    if (t == NULL) {
        return NULL;
    }

    for (int u = 0; u < g->num_vertices; u++) {
        for (int v = 0; v < g->num_vertices; v++) {
            if (u != v) {
                t->dist[u][v] = g->adj[u][v] ? 1 : 2;
            }
        }
    }

    return t;
}
