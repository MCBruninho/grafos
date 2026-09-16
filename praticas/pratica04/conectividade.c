#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"

GrafoLista *criar_grafo(int n) {
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->lista = (No **)malloc(sizeof(No *) * n);
    for (int i = 0; i < n; i++) {
        g->lista[i] = NULL;
    }
    return g;
}

static void inserir(GrafoLista *g, int u, int v) {
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->proximo = NULL;

    if (g->lista[u] == NULL) {
        g->lista[u] = no;
        return;
    }

    No *atual = g->lista[u];
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = no;
}

void adicionar_aresta_nao_direcionada(GrafoLista *g, int u, int v) {
    inserir(g, u, v);
    inserir(g, v, u);
}

void liberar_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->lista[i];
        while (atual != NULL) {
            No *proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }
    free(g->lista);
    free(g);
}

void imprimir_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("  %d ->", i + 1);
        for (No *atual = g->lista[i]; atual != NULL; atual = atual->proximo) {
            printf(" %d", atual->vertice + 1);
        }
        printf("\n");
    }
}

int grau(GrafoLista *g, int v) {
    int d = 0;
    for (No *atual = g->lista[v]; atual != NULL; atual = atual->proximo) {
        d++;
    }
    return d;
}

/* Cada aresta aparece duas vezes nas listas, por isso a divisao por 2. */
int contar_arestas(GrafoLista *g) {
    int total = 0;
    for (int v = 0; v < g->num_vertices; v++) {
        total += grau(g, v);
    }
    return total / 2;
}

int existe_aresta(GrafoLista *g, int u, int v) {
    for (No *atual = g->lista[u]; atual != NULL; atual = atual->proximo) {
        if (atual->vertice == v) {
            return 1;
        }
    }
    return 0;
}

static int menor(int a, int b) {
    return (a < b) ? a : b;
}

void dfs_articulacoes(GrafoLista *g, int u, int *descoberta, int *low, int *pai,
                      int *eh_articulacao, int *tempo) {
    int filhos = 0;

    (*tempo)++;
    descoberta[u] = *tempo;
    low[u] = *tempo;

    for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
        int v = no->vertice;

        if (descoberta[v] == 0) {
            /* aresta da arvore: desce e depois propaga o low do filho */
            filhos++;
            pai[v] = u;
            dfs_articulacoes(g, v, descoberta, low, pai, eh_articulacao, tempo);
            low[u] = menor(low[u], low[v]);

            /* u nao e raiz e o filho v nao alcanca nada acima de u: cortar u separa v */
            if (pai[u] != -1 && low[v] >= descoberta[u]) {
                eh_articulacao[u] = 1;
            }
        } else if (v != pai[u]) {
            /* aresta de retorno: v ja foi visitado e nao e o pai de u */
            low[u] = menor(low[u], descoberta[v]);
        }
    }

    /* a raiz so e articulacao se tiver mais de uma subarvore */
    if (pai[u] == -1 && filhos > 1) {
        eh_articulacao[u] = 1;
    }
}

int *encontrar_articulacoes(GrafoLista *g, int *quantidade) {
    int n = g->num_vertices;
    int *descoberta = (int *)calloc(n, sizeof(int));
    int *low = (int *)calloc(n, sizeof(int));
    int *pai = (int *)malloc(sizeof(int) * n);
    int *eh_articulacao = (int *)calloc(n, sizeof(int));
    int tempo = 0;

    for (int v = 0; v < n; v++) {
        pai[v] = -1;
    }

    /* um grafo desconexo tem uma raiz de DFS por componente */
    for (int v = 0; v < n; v++) {
        if (descoberta[v] == 0) {
            dfs_articulacoes(g, v, descoberta, low, pai, eh_articulacao, &tempo);
        }
    }

    int total = 0;
    for (int v = 0; v < n; v++) {
        total += eh_articulacao[v];
    }

    int *resultado = NULL;
    if (total > 0) {
        resultado = (int *)malloc(sizeof(int) * total);
        int i = 0;
        for (int v = 0; v < n; v++) {
            if (eh_articulacao[v]) {
                resultado[i++] = v;
            }
        }
    }

    free(descoberta);
    free(low);
    free(pai);
    free(eh_articulacao);

    *quantidade = total;
    return resultado;
}

/* ========================= Tarjan: pontes ========================= */

static void dfs_pontes(GrafoLista *g, int u, int *descoberta, int *low, int *pai,
                       Aresta *pontes, int *total, int *tempo) {
    (*tempo)++;
    descoberta[u] = *tempo;
    low[u] = *tempo;

    for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
        int v = no->vertice;

        if (descoberta[v] == 0) {
            pai[v] = u;
            dfs_pontes(g, v, descoberta, low, pai, pontes, total, tempo);
            low[u] = menor(low[u], low[v]);

            /* nenhuma aresta de retorno sai da subarvore de v: (u, v) e a unica ligacao */
            if (low[v] > descoberta[u]) {
                pontes[*total].u = u;
                pontes[*total].v = v;
                (*total)++;
            }
        } else if (v != pai[u]) {
            low[u] = menor(low[u], descoberta[v]);
        }
    }
}

Aresta *detectar_pontes(GrafoLista *g, int *quantidade) {
    int n = g->num_vertices;
    int m = contar_arestas(g);
    int *descoberta = (int *)calloc(n, sizeof(int));
    int *low = (int *)calloc(n, sizeof(int));
    int *pai = (int *)malloc(sizeof(int) * n);
    /* no maximo m pontes; garante ao menos 1 posicao para o malloc nao ser de tamanho 0 */
    Aresta *pontes = (Aresta *)malloc(sizeof(Aresta) * (m > 0 ? m : 1));
    int total = 0;
    int tempo = 0;

    for (int v = 0; v < n; v++) {
        pai[v] = -1;
    }

    for (int v = 0; v < n; v++) {
        if (descoberta[v] == 0) {
            dfs_pontes(g, v, descoberta, low, pai, pontes, &total, &tempo);
        }
    }

    free(descoberta);
    free(low);
    free(pai);

    if (total == 0) {
        free(pontes);
        *quantidade = 0;
        return NULL;
    }

    *quantidade = total;
    return pontes;
}
