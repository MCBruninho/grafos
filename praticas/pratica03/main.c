#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

static void linha(const char *titulo) {
    printf("\n=== %s ===\n", titulo);
}

/* Imprime a ordem topologica. Se nomes for NULL, mostra apenas os numeros (base 1). */
static void imprimir_ordem(int *ordem, int tamanho, const char **nomes) {
    for (int i = 0; i < tamanho; i++) {
        if (i > 0) printf(" -> ");
        if (nomes != NULL) {
            printf("%s", nomes[ordem[i]]);
        } else {
            printf("%d", ordem[i] + 1);
        }
    }
    printf("\n");
}

/* Roda os dois algoritmos sobre o mesmo digrafo e compara os resultados. */
static void analisar(GrafoLista *g, const char *nome, const char **nomes) {
    int tamanho = 0;
    int *ordem;

    printf("\n##### %s #####\n", nome);

    linha("Lista de adjacencia (u -> vizinhos)");
    imprimir_grafo(g);

    linha("Graus de entrada");
    int *grau_entrada = (int *)malloc(sizeof(int) * g->num_vertices);
    calcular_graus_entrada(g, grau_entrada);
    for (int v = 0; v < g->num_vertices; v++) {
        printf("  %d: %d\n", v + 1, grau_entrada[v]);
    }
    free(grau_entrada);

    linha("Deteccao de ciclos");
    printf("%s\n", eh_dag(g) ? "O grafo e um DAG (aciclico)" : "O grafo POSSUI ciclo: nao e um DAG");

    linha("Ordenacao topologica - Kahn (fila + grau de entrada)");
    ordem = ordenacao_topologica_kahn(g, &tamanho);
    if (ordem == NULL) {
        printf("ERRO: o grafo possui ciclo, a ordenacao topologica e impossivel.\n");
    } else {
        imprimir_ordem(ordem, tamanho, nomes);
        free(ordem);
    }

    linha("Ordenacao topologica - DFS (empilha na saida)");
    ordem = ordenacao_topologica_dfs(g, &tamanho);
    if (ordem == NULL) {
        printf("ERRO: o grafo possui ciclo, a ordenacao topologica e impossivel.\n");
    } else {
        imprimir_ordem(ordem, tamanho, nomes);
        free(ordem);
    }
}

int main() {
    /* Grafo 1: pre-requisitos de disciplinas (DAG classico).
       1 Algoritmos -> 2 Estruturas -> 3 Grafos ; 4 Calculo -> 5 Estatistica ; 6 Projeto no fim */
    const char *disciplinas[] = {
        "Algoritmos", "Estruturas", "Grafos", "Calculo", "Estatistica", "Projeto"
    };
    GrafoLista *g1 = criar_grafo(6);
    adicionar_aresta(g1, 0, 1); /* Algoritmos -> Estruturas */
    adicionar_aresta(g1, 1, 2); /* Estruturas -> Grafos */
    adicionar_aresta(g1, 0, 4); /* Algoritmos -> Estatistica */
    adicionar_aresta(g1, 3, 4); /* Calculo    -> Estatistica */
    adicionar_aresta(g1, 2, 5); /* Grafos     -> Projeto */
    adicionar_aresta(g1, 4, 5); /* Estatistica-> Projeto */

    /* Grafo 2: DAG com dois vertices isolados e varias ordens validas. */
    GrafoLista *g2 = criar_grafo(7);
    adicionar_aresta(g2, 0, 2);
    adicionar_aresta(g2, 1, 2);
    adicionar_aresta(g2, 2, 3);
    adicionar_aresta(g2, 3, 4);
    /* vertices 6 e 7 nao possuem arestas */

    /* Grafo 3: digrafo com ciclo 2 -> 3 -> 4 -> 2 (nao e DAG). */
    GrafoLista *g3 = criar_grafo(5);
    adicionar_aresta(g3, 0, 1);
    adicionar_aresta(g3, 1, 2);
    adicionar_aresta(g3, 2, 3);
    adicionar_aresta(g3, 3, 1); /* aresta de retorno: fecha o ciclo */
    adicionar_aresta(g3, 3, 4);

    analisar(g1, "Grafo 1: pre-requisitos de disciplinas (DAG)", disciplinas);
    analisar(g2, "Grafo 2: DAG com vertices isolados", NULL);
    analisar(g3, "Grafo 3: digrafo com ciclo", NULL);

    liberar_grafo(g1);
    liberar_grafo(g2);
    liberar_grafo(g3);

    return 0;
}
