#include "coloracao.h"

#include <stdio.h>
#include <stdlib.h>

GrafoLista *grafo_criar(int num_vertices) {
    if (num_vertices < 0) {
        return NULL;
    }

    GrafoLista *g = malloc(sizeof(GrafoLista));
    if (g == NULL) {
        return NULL;
    }

    g->num_vertices = num_vertices;
    g->adj = calloc((size_t)num_vertices, sizeof(NoAdj *));

    if (num_vertices > 0 && g->adj == NULL) {
        free(g);
        return NULL;
    }

    return g;
}

void grafo_adicionar_aresta(GrafoLista *g, int origem, int destino) {
    if (g == NULL ||
        origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices) {
        return;
    }

    NoAdj *novo = malloc(sizeof(NoAdj));
    if (novo == NULL) {
        return;
    }

    novo->vertice = destino;
    novo->prox = g->adj[origem];
    g->adj[origem] = novo;

    novo = malloc(sizeof(NoAdj));
    if (novo == NULL) {
        return;
    }

    novo->vertice = origem;
    novo->prox = g->adj[destino];
    g->adj[destino] = novo;
}

void grafo_destruir(GrafoLista *g) {
    if (g == NULL) {
        return;
    }

    for (int i = 0; i < g->num_vertices; i++) {
        NoAdj *atual = g->adj[i];

        while (atual != NULL) {
            NoAdj *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(g->adj);
    free(g);
}

static int grau_vertice(GrafoLista *g, int v) {
    int grau = 0;

    for (NoAdj *p = g->adj[v]; p != NULL; p = p->prox) {
        grau++;
    }

    return grau;
}

static int menor_cor_disponivel(
    GrafoLista *g,
    int v,
    int *cores,
    int quantidade_maxima
) {
    int *usada = calloc((size_t)quantidade_maxima, sizeof(int));

    if (usada == NULL) {
        return -1;
    }

    for (NoAdj *p = g->adj[v]; p != NULL; p = p->prox) {
        int vizinho = p->vertice;

        if (cores[vizinho] >= 0 &&
            cores[vizinho] < quantidade_maxima) {
            usada[cores[vizinho]] = 1;
        }
    }

    int cor = 0;

    while (cor < quantidade_maxima && usada[cor]) {
        cor++;
    }

    free(usada);

    if (cor == quantidade_maxima) {
        return -1;
    }

    return cor;
}

int *coloracao_gulosa(GrafoLista *g, int *num_cores) {
    if (g == NULL || num_cores == NULL) {
        return NULL;
    }

    int n = g->num_vertices;

    if (n == 0) {
        *num_cores = 0;
        return NULL;
    }

    int *cores = malloc((size_t)n * sizeof(int));

    if (cores == NULL) {
        *num_cores = 0;
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        cores[i] = -1;
    }

    int maior_cor = -1;

    for (int v = 0; v < n; v++) {
        int cor = menor_cor_disponivel(g, v, cores, n);

        if (cor < 0) {
            free(cores);
            *num_cores = 0;
            return NULL;
        }

        cores[v] = cor;

        if (cor > maior_cor) {
            maior_cor = cor;
        }
    }

    *num_cores = maior_cor + 1;

    return cores;
}

typedef struct {
    int vertice;
    int grau;
} VerticeGrau;

static int comparar_grau_decrescente(
    const void *a,
    const void *b
) {
    const VerticeGrau *va = a;
    const VerticeGrau *vb = b;

    if (va->grau != vb->grau) {
        return vb->grau - va->grau;
    }

    return va->vertice - vb->vertice;
}

int *coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    if (g == NULL || num_cores == NULL) {
        return NULL;
    }

    int n = g->num_vertices;

    if (n == 0) {
        *num_cores = 0;
        return NULL;
    }

    VerticeGrau *ordem = malloc((size_t)n * sizeof(VerticeGrau));
    int *cores = malloc((size_t)n * sizeof(int));

    if (ordem == NULL || cores == NULL) {
        free(ordem);
        free(cores);
        *num_cores = 0;
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        ordem[i].vertice = i;
        ordem[i].grau = grau_vertice(g, i);
        cores[i] = -1;
    }

    qsort(
        ordem,
        (size_t)n,
        sizeof(VerticeGrau),
        comparar_grau_decrescente
    );

    int maior_cor = -1;

    for (int i = 0; i < n; i++) {
        int v = ordem[i].vertice;
        int cor = menor_cor_disponivel(g, v, cores, n);

        if (cor < 0) {
            free(ordem);
            free(cores);
            *num_cores = 0;
            return NULL;
        }

        cores[v] = cor;

        if (cor > maior_cor) {
            maior_cor = cor;
        }
    }

    *num_cores = maior_cor + 1;

    free(ordem);

    return cores;
}

int eh_bipartido(GrafoLista *g) {
    if (g == NULL) {
        return 0;
    }

    int n = g->num_vertices;

    if (n == 0) {
        return 1;
    }

    int *cores = malloc((size_t)n * sizeof(int));
    int *fila = malloc((size_t)n * sizeof(int));

    if (cores == NULL || fila == NULL) {
        free(cores);
        free(fila);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        cores[i] = -1;
    }

    for (int inicio = 0; inicio < n; inicio++) {
        if (cores[inicio] != -1) {
            continue;
        }

        int inicio_fila = 0;
        int fim_fila = 0;

        cores[inicio] = 0;
        fila[fim_fila++] = inicio;

        while (inicio_fila < fim_fila) {
            int v = fila[inicio_fila++];

            for (NoAdj *p = g->adj[v]; p != NULL; p = p->prox) {
                int vizinho = p->vertice;

                if (cores[vizinho] == -1) {
                    cores[vizinho] = 1 - cores[v];
                    fila[fim_fila++] = vizinho;
                } else if (cores[vizinho] == cores[v]) {
                    free(cores);
                    free(fila);
                    return 0;
                }
            }
        }
    }

    free(cores);
    free(fila);

    return 1;
}