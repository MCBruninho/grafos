#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cobertura.h"

#define PROBABILIDADE_ARESTA 0.5
#define SEMENTE 2026u
#define TEMPO_MINIMO_MEDICAO 0.05 /* segundos */

typedef int (*FuncaoCobertura)(const Grafo *, int *);

static void imprimir_cobertura(const char *nome, const int *cobertura, int n, int tamanho) {
    printf("%s (tamanho %d): { ", nome, tamanho);

    for (int v = 0; v < n; v++) {
        if (cobertura[v]) {
            printf("%d ", v);
        }
    }

    printf("}\n");
}

/*
 * Mede o tempo medio (em ms) de uma execucao. Como clock() tem baixa
 * resolucao, repete a funcao ate acumular TEMPO_MINIMO_MEDICAO segundos.
 */
static double medir_ms(FuncaoCobertura f, const Grafo *g, int *cobertura, int *tamanho) {
    long repeticoes = 0;
    clock_t inicio = clock();
    clock_t agora;

    do {
        *tamanho = f(g, cobertura);
        repeticoes++;
        agora = clock();
    } while ((double)(agora - inicio) / CLOCKS_PER_SEC < TEMPO_MINIMO_MEDICAO);

    return 1000.0 * (double)(agora - inicio) / CLOCKS_PER_SEC / (double)repeticoes;
}

static void exemplo_pequeno(void) {
    printf("1. Exemplo pequeno\n");
    printf("Arestas: 0-1, 0-2, 1-2, 1-3, 2-4, 3-4, 3-5\n\n");

    Grafo *g = grafo_criar(6);
    if (g == NULL) {
        fprintf(stderr, "Erro ao criar o grafo.\n");
        return;
    }

    grafo_adicionar_aresta(g, 0, 1);
    grafo_adicionar_aresta(g, 0, 2);
    grafo_adicionar_aresta(g, 1, 2);
    grafo_adicionar_aresta(g, 1, 3);
    grafo_adicionar_aresta(g, 2, 4);
    grafo_adicionar_aresta(g, 3, 4);
    grafo_adicionar_aresta(g, 3, 5);

    int bt[6];
    int gulosa[6];
    int tam_bt = cobertura_minima_bt(g, bt);
    int tam_gulosa = cobertura_gulosa(g, gulosa);

    imprimir_cobertura("Backtracking", bt, 6, tam_bt);
    printf("eh_cobertura: %s\n", eh_cobertura(g, bt) ? "SIM" : "NAO");

    imprimir_cobertura("Gulosa      ", gulosa, 6, tam_gulosa);
    printf("eh_cobertura: %s\n", eh_cobertura(g, gulosa) ? "SIM" : "NAO");

    int vazia[6] = {0};
    printf("Conjunto vazio eh_cobertura: %s\n\n", eh_cobertura(g, vazia) ? "SIM" : "NAO");

    grafo_destruir(g);
}

static void experimento(void) {
    const int tamanhos[] = {5, 8, 10, 12, 15};
    const int qtd = (int)(sizeof(tamanhos) / sizeof(tamanhos[0]));

    printf("2. Experimento: forca bruta (backtracking) x heuristica gulosa\n");
    printf("Grafos aleatorios G(n, p = %.2f), semente %u\n\n", PROBABILIDADE_ARESTA, SEMENTE);

    printf("+-----+---------+--------+--------------+--------+--------------+--------+\n");
    printf("|  n  | arestas | |C| BT |  tempo BT ms | |C| GL |  tempo GL ms | razao  |\n");
    printf("+-----+---------+--------+--------------+--------+--------------+--------+\n");

    for (int i = 0; i < qtd; i++) {
        int n = tamanhos[i];
        Grafo *g = grafo_aleatorio(n, PROBABILIDADE_ARESTA, SEMENTE + (unsigned)n);
        int *bt = malloc((size_t)n * sizeof(int));
        int *gl = malloc((size_t)n * sizeof(int));

        if (g == NULL || bt == NULL || gl == NULL) {
            fprintf(stderr, "Erro de memoria para n = %d.\n", n);
            grafo_destruir(g);
            free(bt);
            free(gl);
            return;
        }

        int tam_bt = 0;
        int tam_gl = 0;
        double t_bt = medir_ms(cobertura_minima_bt, g, bt, &tam_bt);
        double t_gl = medir_ms(cobertura_gulosa, g, gl, &tam_gl);

        if (!eh_cobertura(g, bt) || !eh_cobertura(g, gl)) {
            fprintf(stderr, "ERRO: cobertura invalida para n = %d.\n", n);
        }

        printf("| %3d | %7d | %6d | %12.6f | %6d | %12.6f | %6.3f |\n",
               n, g->num_arestas, tam_bt, t_bt, tam_gl, t_gl,
               tam_bt > 0 ? (double)tam_gl / tam_bt : 1.0);

        grafo_destruir(g);
        free(bt);
        free(gl);
    }

    printf("+-----+---------+--------+--------------+--------+--------------+--------+\n");
    printf("razao = |C gulosa| / |C otima| (1.000 = gulosa encontrou o otimo)\n");
}

int main(void) {
    printf("========================================\n");
    printf("   PRATICA 09 - COBERTURA DE VERTICES\n");
    printf("========================================\n\n");

    exemplo_pequeno();
    experimento();

    return 0;
}
