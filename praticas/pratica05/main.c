#include <stdio.h>
#include <stdlib.h>

#include "coloracao.h"

static void imprimir_coloracao(
    const char *nome,
    int *cores,
    int num_vertices,
    int num_cores
) {
    printf("%s\n", nome);

    if (cores == NULL && num_vertices > 0) {
        printf("Erro ao realizar a coloracao.\n\n");
        return;
    }

    printf("Numero de cores: %d\n", num_cores);

    for (int i = 0; i < num_vertices; i++) {
        printf("Vertice %d -> cor %d\n", i, cores[i]);
    }

    printf("\n");
}

int main(void) {
    GrafoLista *g = grafo_criar(4);

    if (g == NULL) {
        fprintf(stderr, "Erro ao criar o grafo.\n");
        return 1;
    }

    grafo_adicionar_aresta(g, 0, 1);
    grafo_adicionar_aresta(g, 0, 2);
    grafo_adicionar_aresta(g, 1, 2);
    grafo_adicionar_aresta(g, 1, 3);
    grafo_adicionar_aresta(g, 2, 3);

    printf("========================================\n");
    printf("      PRATICA 05 - COLORACAO GRAFOS\n");
    printf("========================================\n\n");

    int num_cores_gulosa = 0;
    int *cores_gulosa = coloracao_gulosa(g, &num_cores_gulosa);

    imprimir_coloracao(
        "1. Coloracao Gulosa",
        cores_gulosa,
        g->num_vertices,
        num_cores_gulosa
    );

    int num_cores_wp = 0;
    int *cores_wp = coloracao_welsh_powell(g, &num_cores_wp);

    imprimir_coloracao(
        "2. Coloracao Welsh-Powell",
        cores_wp,
        g->num_vertices,
        num_cores_wp
    );

    printf("3. Verificacao de Biparticao\n");

    if (eh_bipartido(g)) {
        printf("O grafo E bipartido.\n");
    } else {
        printf("O grafo NAO e bipartido.\n");
    }

    printf("\n");

    free(cores_gulosa);
    free(cores_wp);
    grafo_destruir(g);

    GrafoLista *bipartido = grafo_criar(4);

    if (bipartido == NULL) {
        fprintf(stderr, "Erro ao criar o segundo grafo.\n");
        return 1;
    }

    grafo_adicionar_aresta(bipartido, 0, 1);
    grafo_adicionar_aresta(bipartido, 1, 2);
    grafo_adicionar_aresta(bipartido, 2, 3);
    grafo_adicionar_aresta(bipartido, 3, 0);

    printf("4. Segundo teste - grafo ciclo C4\n");

    if (eh_bipartido(bipartido)) {
        printf("O grafo E bipartido (2-coloravel).\n");
    } else {
        printf("O grafo NAO e bipartido.\n");
    }

    grafo_destruir(bipartido);

    return 0;
}