#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

static void linha(const char *titulo) {
    printf("\n=== %s ===\n", titulo);
}

/* Roda todas as buscas e aplicacoes sobre um grafo nao direcionado. */
static void analisar(GrafoLista *g, const char *nome, int origem) {
    int n = g->num_vertices;
    int *dist = (int *)malloc(sizeof(int) * n);
    int *pred = (int *)malloc(sizeof(int) * n);
    int *visitado = (int *)calloc(n, sizeof(int));
    int *ordem = (int *)malloc(sizeof(int) * n);
    int n_ordem = 0;

    printf("\n##### %s #####\n", nome);

    linha("Lista de adjacencia");
    imprimir_grafo(g);

    linha("BFS (fila)");
    printf("Origem: %d\n", origem + 1);
    bfs(g, origem, dist, pred);

    printf("\nDistancias a partir de %d:\n", origem + 1);
    for (int i = 0; i < n; i++) {
        if (dist[i] == -1) {
            printf("  %d: inalcancavel\n", i + 1);
        } else {
            printf("  %d: %d  | caminho: ", i + 1, dist[i]);
            imprimir_caminho(pred, i);
            printf("\n");
        }
    }

    linha("DFS recursiva (pilha de chamadas)");
    for (int i = 0; i < n; i++) {
        visitado[i] = 0;
        pred[i] = -1;
    }
    n_ordem = 0;
    dfs_recursiva(g, origem, visitado, pred, ordem, &n_ordem);
    printf("Ordem de visita: ");
    for (int i = 0; i < n_ordem; i++) printf("%d ", ordem[i] + 1);
    printf("\n");

    linha("DFS iterativa (pilha explicita)");
    for (int i = 0; i < n; i++) {
        visitado[i] = 0;
        pred[i] = -1;
    }
    n_ordem = 0;
    dfs_iterativa(g, origem, visitado, pred, ordem, &n_ordem);
    printf("Ordem de visita: ");
    for (int i = 0; i < n_ordem; i++) printf("%d ", ordem[i] + 1);
    printf("\n");

    linha("Componentes conexos");
    printf("Total: %d\n", contar_componentes(g));

    linha("Ciclos");
    printf("%s\n", tem_ciclo(g) ? "O grafo possui ciclo" : "O grafo e aciclico (floresta)");

    linha("Biparticao");
    printf("%s\n", eh_bipartido(g) ? "O grafo e bipartido" : "O grafo NAO e bipartido");

    free(dist);
    free(pred);
    free(visitado);
    free(ordem);
}

int main() {
    /* Grafo 1: ciclo par (1-2-4-3-1), um caminho ate 5 e um componente isolado {6,7} */
    GrafoLista *g1 = criar_grafo(7);
    adicionar_aresta_nao_direcionada(g1, 0, 1);
    adicionar_aresta_nao_direcionada(g1, 0, 2);
    adicionar_aresta_nao_direcionada(g1, 1, 3);
    adicionar_aresta_nao_direcionada(g1, 2, 3);
    adicionar_aresta_nao_direcionada(g1, 3, 4);
    adicionar_aresta_nao_direcionada(g1, 5, 6);

    /* Grafo 2: triangulo 1-2-3 (ciclo impar) com uma cauda 3-4-5 */
    GrafoLista *g2 = criar_grafo(5);
    adicionar_aresta_nao_direcionada(g2, 0, 1);
    adicionar_aresta_nao_direcionada(g2, 1, 2);
    adicionar_aresta_nao_direcionada(g2, 2, 0);
    adicionar_aresta_nao_direcionada(g2, 2, 3);
    adicionar_aresta_nao_direcionada(g2, 3, 4);

    /* Grafo 3: arvore (sem ciclos, conexa e sempre bipartida) */
    GrafoLista *g3 = criar_grafo(5);
    adicionar_aresta_nao_direcionada(g3, 0, 1);
    adicionar_aresta_nao_direcionada(g3, 0, 2);
    adicionar_aresta_nao_direcionada(g3, 2, 3);
    adicionar_aresta_nao_direcionada(g3, 2, 4);

    analisar(g1, "Grafo 1: dois componentes, ciclo par", 0);
    analisar(g2, "Grafo 2: triangulo com cauda", 0);
    analisar(g3, "Grafo 3: arvore", 0);

    liberar_grafo(g1);
    liberar_grafo(g2);
    liberar_grafo(g3);

    return 0;
}
