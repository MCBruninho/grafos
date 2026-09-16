#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"
#include "planaridade.h"

static void linha(const char *titulo) {
    printf("\n=== %s ===\n", titulo);
}

/* Roda os testes de conectividade e de planaridade sobre o mesmo grafo. */
static void analisar(GrafoLista *g, const char *nome) {
    int n = g->num_vertices;
    int m = contar_arestas(g);
    int quantidade = 0;

    printf("\n##### %s #####\n", nome);
    printf("n = %d vertices, m = %d arestas\n", n, m);

    linha("Lista de adjacencia");
    imprimir_grafo(g);

    linha("Vertices de corte (articulacoes) - Tarjan");
    int *articulacoes = encontrar_articulacoes(g, &quantidade);
    if (articulacoes == NULL) {
        printf("Nenhum vertice de corte: o grafo e biconexo.\n");
    } else {
        printf("Total: %d\n  ", quantidade);
        for (int i = 0; i < quantidade; i++) {
            printf("%d ", articulacoes[i] + 1);
        }
        printf("\n");
        free(articulacoes);
    }

    linha("Pontes (arestas de corte) - low[v] > descoberta[u]");
    Aresta *pontes = detectar_pontes(g, &quantidade);
    if (pontes == NULL) {
        printf("Nenhuma ponte: toda aresta esta em algum ciclo.\n");
    } else {
        printf("Total: %d\n", quantidade);
        for (int i = 0; i < quantidade; i++) {
            printf("  (%d, %d)\n", pontes[i].u + 1, pontes[i].v + 1);
        }
        free(pontes);
    }

    linha("Planaridade - formula de Euler (m <= 3n - 6)");
    if (n < 3) {
        printf("n < 3: planar trivialmente.\n");
    } else {
        printf("m = %d, 3n - 6 = %d -> %s\n", m, 3 * n - 6,
               eh_planar_euler(g) ? "passa no teste (pode ser planar)"
                                  : "FALHA: o grafo nao e planar");
    }

    linha("Planaridade - heuristica de Kuratowski (n <= 10)");
    if (n > 10) {
        printf("n > 10: forca bruta nao aplicada.\n");
    } else {
        printf("Subdivisao de K5  : %s\n", contem_subdivisao_k5(g) ? "ENCONTRADA" : "nao encontrada");
        printf("Subdivisao de K3,3: %s\n", contem_subdivisao_k33(g) ? "ENCONTRADA" : "nao encontrada");
    }

    linha("Conclusao");
    int resultado = verificar_planaridade(g);
    if (resultado == 1) {
        printf("O grafo E PLANAR.\n");
    } else if (resultado == 0) {
        printf("O grafo NAO E PLANAR.\n");
    } else {
        printf("Indeterminado: passou em Euler, mas n > 10 para o teste de Kuratowski.\n");
    }
}

int main() {
    /* Grafo 1: dois triangulos ligados por uma ponte, mais um vertice pendurado.
       Articulacoes esperadas: 2, 4 e 6. Pontes esperadas: (2,4) e (6,7). */
    GrafoLista *g1 = criar_grafo(7);
    adicionar_aresta_nao_direcionada(g1, 0, 1);
    adicionar_aresta_nao_direcionada(g1, 1, 2);
    adicionar_aresta_nao_direcionada(g1, 2, 0);
    adicionar_aresta_nao_direcionada(g1, 1, 3); /* ponte */
    adicionar_aresta_nao_direcionada(g1, 3, 4);
    adicionar_aresta_nao_direcionada(g1, 4, 5);
    adicionar_aresta_nao_direcionada(g1, 5, 3);
    adicionar_aresta_nao_direcionada(g1, 5, 6); /* ponte */

    /* Grafo 2: K4 - biconexo e planar (m = 6 = 3n - 6). */
    GrafoLista *g2 = criar_grafo(4);
    for (int u = 0; u < 4; u++) {
        for (int v = u + 1; v < 4; v++) {
            adicionar_aresta_nao_direcionada(g2, u, v);
        }
    }

    /* Grafo 3: K5 - o primeiro grafo de Kuratowski, reprovado ja pela formula de Euler. */
    GrafoLista *g3 = criar_grafo(5);
    for (int u = 0; u < 5; u++) {
        for (int v = u + 1; v < 5; v++) {
            adicionar_aresta_nao_direcionada(g3, u, v);
        }
    }

    /* Grafo 4: K3,3 - passa na formula de Euler (9 <= 12) mas nao e planar.
       Mostra por que Euler sozinho nao basta. */
    GrafoLista *g4 = criar_grafo(6);
    for (int a = 0; a < 3; a++) {
        for (int b = 3; b < 6; b++) {
            adicionar_aresta_nao_direcionada(g4, a, b);
        }
    }

    /* Grafo 5: subdivisao de K3,3 - a aresta 1-4 virou o caminho 1-7-4.
       Nenhum vertice tem grau 4, mas a subdivisao continua la. */
    GrafoLista *g5 = criar_grafo(7);
    for (int a = 0; a < 3; a++) {
        for (int b = 3; b < 6; b++) {
            if (a == 0 && b == 3) {
                continue; /* aresta subdividida */
            }
            adicionar_aresta_nao_direcionada(g5, a, b);
        }
    }
    adicionar_aresta_nao_direcionada(g5, 0, 6);
    adicionar_aresta_nao_direcionada(g5, 6, 3);

    analisar(g1, "Grafo 1: triangulos ligados por ponte");
    analisar(g2, "Grafo 2: K4 (planar)");
    analisar(g3, "Grafo 3: K5 (nao planar)");
    analisar(g4, "Grafo 4: K3,3 (nao planar, mas passa em Euler)");
    analisar(g5, "Grafo 5: subdivisao de K3,3");

    liberar_grafo(g1);
    liberar_grafo(g2);
    liberar_grafo(g3);
    liberar_grafo(g4);
    liberar_grafo(g5);

    return 0;
}
