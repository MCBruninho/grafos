#include "cobertura.h"

#include <stdlib.h>
#include <string.h>

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
/* Verificacao                                                         */
/* ------------------------------------------------------------------ */

int eh_cobertura(const Grafo *g, const int *cobertura) {
    if (g == NULL || cobertura == NULL) {
        return 0;
    }

    for (int u = 0; u < g->num_vertices; u++) {
        for (int v = u + 1; v < g->num_vertices; v++) {
            if (g->adj[u][v] && !cobertura[u] && !cobertura[v]) {
                return 0;
            }
        }
    }

    return 1;
}

/* ------------------------------------------------------------------ */
/* Backtracking com poda por limite (branch and bound)                 */
/* ------------------------------------------------------------------ */

typedef struct {
    const Grafo *g;
    int *atual;        /* cobertura parcial sendo construida */
    int *melhor;       /* melhor cobertura encontrada ate agora */
    int melhor_tamanho;
} EstadoBT;

/*
 * Procura a primeira aresta {u, v} ainda nao coberta.
 * Retorna 1 se encontrou, 0 se todas estao cobertas.
 */
static int primeira_aresta_descoberta(
    const Grafo *g,
    const int *cobertura,
    int *u_out,
    int *v_out
) {
    for (int u = 0; u < g->num_vertices; u++) {
        if (cobertura[u]) {
            continue;
        }

        for (int v = u + 1; v < g->num_vertices; v++) {
            if (g->adj[u][v] && !cobertura[v]) {
                *u_out = u;
                *v_out = v;
                return 1;
            }
        }
    }

    return 0;
}

/*
 * Toda aresta {u, v} descoberta obriga u ou v a entrar na cobertura.
 * Por isso ramificamos em apenas duas opcoes: incluir u ou incluir v.
 *
 * Poda por limite: se a cobertura parcial ja tem tamanho >= melhor
 * conhecida e ainda falta cobrir alguma aresta, nenhuma solucao desse
 * ramo pode ser melhor, entao abandonamos o ramo.
 */
static void bt_recursivo(EstadoBT *e, int tamanho) {
    int u;
    int v;

    if (!primeira_aresta_descoberta(e->g, e->atual, &u, &v)) {
        /* Todas as arestas cobertas: solucao completa. */
        if (tamanho < e->melhor_tamanho) {
            e->melhor_tamanho = tamanho;
            memcpy(
                e->melhor,
                e->atual,
                (size_t)e->g->num_vertices * sizeof(int)
            );
        }
        return;
    }

    /* Precisamos de pelo menos mais 1 vertice: poda. */
    if (tamanho + 1 >= e->melhor_tamanho) {
        return;
    }

    /* Ramo 1: incluir u. */
    e->atual[u] = 1;
    bt_recursivo(e, tamanho + 1);
    e->atual[u] = 0;

    /* Ramo 2: incluir v. */
    e->atual[v] = 1;
    bt_recursivo(e, tamanho + 1);
    e->atual[v] = 0;
}

int cobertura_minima_bt(const Grafo *g, int *cobertura) {
    if (g == NULL || cobertura == NULL) {
        return -1;
    }

    int n = g->num_vertices;

    EstadoBT e;
    e.g = g;
    e.atual = calloc((size_t)(n > 0 ? n : 1), sizeof(int));
    e.melhor = cobertura;

    if (e.atual == NULL) {
        return -1;
    }

    /* Limite inicial: todos os vertices (sempre e uma cobertura valida). */
    for (int i = 0; i < n; i++) {
        e.melhor[i] = 1;
    }
    e.melhor_tamanho = n;

    bt_recursivo(&e, 0);

    free(e.atual);

    return e.melhor_tamanho;
}

/* ------------------------------------------------------------------ */
/* Heuristica gulosa: vertice de maior grau restante                    */
/* ------------------------------------------------------------------ */

int cobertura_gulosa(const Grafo *g, int *cobertura) {
    if (g == NULL || cobertura == NULL) {
        return -1;
    }

    int n = g->num_vertices;
    int *grau = calloc((size_t)(n > 0 ? n : 1), sizeof(int));

    if (grau == NULL) {
        return -1;
    }

    for (int u = 0; u < n; u++) {
        cobertura[u] = 0;

        for (int v = 0; v < n; v++) {
            grau[u] += g->adj[u][v];
        }
    }

    int tamanho = 0;
    int restantes = g->num_arestas;

    while (restantes > 0) {
        /* Escolhe o vertice com mais arestas ainda descobertas. */
        int escolhido = -1;

        for (int u = 0; u < n; u++) {
            if (!cobertura[u] &&
                (escolhido == -1 || grau[u] > grau[escolhido])) {
                escolhido = u;
            }
        }

        cobertura[escolhido] = 1;
        tamanho++;

        /* As arestas de 'escolhido' passam a estar cobertas. */
        for (int v = 0; v < n; v++) {
            if (g->adj[escolhido][v] && !cobertura[v]) {
                grau[v]--;
                restantes--;
            }
        }

        grau[escolhido] = 0;
    }

    free(grau);

    return tamanho;
}
