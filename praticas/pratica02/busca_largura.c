#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "busca_largura.h"

Fila *criar_fila(int capacidade) {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->dados = (int *)malloc(sizeof(int) * capacidade);
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

int fila_vazia(Fila *f) {
    return f->tamanho == 0;
}

void enfileirar(Fila *f, int v) {
    if (f->tamanho == f->capacidade) return; /* fila cheia: nada a fazer */
    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

int desenfileirar(Fila *f) {
    if (fila_vazia(f)) return -1;
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return v;
}

void liberar_fila(Fila *f) {
    free(f->dados);
    free(f);
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    Fila *f = criar_fila(g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    dist[origem] = 0;
    enfileirar(f, origem);

    while (!fila_vazia(f)) {
        int u = desenfileirar(f);
        printf("Visita %d (dist %d)\n", u + 1, dist[u]);

        for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
            int v = no->vertice;
            if (dist[v] == -1) {          /* ainda nao descoberto */
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(f, v);
            }
        }
    }

    liberar_fila(f);
}

/* Imprime o caminho da origem ate destino usando o vetor de predecessores. */
void imprimir_caminho(int *pred, int destino) {
    if (pred[destino] != -1) {
        imprimir_caminho(pred, pred[destino]);
        printf(" -> ");
    }
    printf("%d", destino + 1);
}

/* Cada BFS nao iniciada cobre exatamente um componente conexo. */
int contar_componentes(GrafoLista *g) {
    int n = g->num_vertices;
    int *visitado = (int *)calloc(n, sizeof(int));
    Fila *f = criar_fila(n);
    int componentes = 0;

    for (int i = 0; i < n; i++) {
        if (visitado[i]) continue;

        componentes++;
        printf("Componente %d: ", componentes);
        visitado[i] = 1;
        enfileirar(f, i);

        while (!fila_vazia(f)) {
            int u = desenfileirar(f);
            printf("%d ", u + 1);
            for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
                int v = no->vertice;
                if (!visitado[v]) {
                    visitado[v] = 1;
                    enfileirar(f, v);
                }
            }
        }
        printf("\n");
    }

    liberar_fila(f);
    free(visitado);
    return componentes;
}

/* Tenta colorir o grafo com 2 cores (0 e 1) em largura.
   Se uma aresta ligar dois vertices da mesma cor, nao e bipartido. */
int eh_bipartido(GrafoLista *g) {
    int n = g->num_vertices;
    int *cor = (int *)malloc(sizeof(int) * n);
    Fila *f = criar_fila(n);
    int bipartido = 1;

    for (int i = 0; i < n; i++) cor[i] = -1;

    for (int i = 0; i < n && bipartido; i++) {
        if (cor[i] != -1) continue;

        cor[i] = 0;
        enfileirar(f, i);

        while (!fila_vazia(f) && bipartido) {
            int u = desenfileirar(f);
            for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
                int v = no->vertice;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    enfileirar(f, v);
                } else if (cor[v] == cor[u]) {
                    printf("Conflito: aresta {%d, %d} liga dois vertices da mesma cor\n",
                           u + 1, v + 1);
                    bipartido = 0;
                    break;
                }
            }
        }
    }

    if (bipartido) {
        printf("Particao A: ");
        for (int i = 0; i < n; i++) if (cor[i] == 0) printf("%d ", i + 1);
        printf("\nParticao B: ");
        for (int i = 0; i < n; i++) if (cor[i] == 1) printf("%d ", i + 1);
        printf("\n");
    }

    liberar_fila(f);
    free(cor);
    return bipartido;
}
