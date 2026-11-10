#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hamiltoniano.h"
#include "tps.h"

#define PESO_MAXIMO 100
#define SEMENTE 2026u
#define TEMPO_MINIMO_MEDICAO 0.05 /* segundos */

typedef int (*FuncaoTSP)(const InstanciaTSP *, int *);

static void imprimir_sequencia(const int *seq, int n, int fechar) {
    for (int i = 0; i < n; i++) {
        printf("%d%s", seq[i], i < n - 1 ? " -> " : "");
    }

    if (fechar && n > 0) {
        printf(" -> %d", seq[0]);
    }

    printf("\n");
}

/*
 * Mede o tempo medio (em ms) de uma execucao. Como clock() tem baixa
 * resolucao, repete a funcao ate acumular TEMPO_MINIMO_MEDICAO segundos.
 */
static double medir_ms(FuncaoTSP f, const InstanciaTSP *t, int *rota, int *custo) {
    long repeticoes = 0;
    clock_t inicio = clock();
    clock_t agora;

    do {
        *custo = f(t, rota);
        repeticoes++;
        agora = clock();
    } while ((double)(agora - inicio) / CLOCKS_PER_SEC < TEMPO_MINIMO_MEDICAO);

    return 1000.0 * (double)(agora - inicio) / CLOCKS_PER_SEC / (double)repeticoes;
}

static void testar_hamiltoniano(const char *nome, const Grafo *g) {
    int n = g->num_vertices;
    int *seq = malloc((size_t)n * sizeof(int));

    if (seq == NULL) {
        fprintf(stderr, "Erro de memoria.\n");
        return;
    }

    printf("%s\n", nome);

    printf("  Caminho Hamiltoniano: ");
    if (encontrar_caminho_hamiltoniano_bt(g, seq)) {
        imprimir_sequencia(seq, n, 0);
    } else {
        printf("nao existe\n");
    }

    printf("  Ciclo Hamiltoniano:   ");
    if (encontrar_ciclo_hamiltoniano_bt(g, seq)) {
        imprimir_sequencia(seq, n, 1);
    } else {
        printf("nao existe\n");
    }

    /* Confere a reducao: ciclo Hamiltoniano <=> custo otimo do TSP == n. */
    InstanciaTSP *t = grafo_para_tsp(g);
    if (t != NULL) {
        int custo = tsp_forca_bruta(t, seq);
        printf("  Reducao para TSP (pesos 1/2): custo otimo = %d -> %s\n",
               custo, custo == n ? "TEM ciclo (custo == n)" : "NAO tem ciclo (custo > n)");
        tsp_destruir(t);
    }

    printf("\n");
    free(seq);
}

static void parte_hamiltoniano(void) {
    printf("1. Caminho e Ciclo Hamiltoniano (forca bruta)\n\n");

    /* Grafo "casa": quadrado 0-1-2-3 com telhado 4 sobre 0 e 1. */
    Grafo *casa = grafo_criar(5);
    /* 4-0-1-2-3 com triangulo 1-2-3: 4 tem grau 1, logo ha caminho mas nao ciclo. */
    Grafo *pendente = grafo_criar(5);
    /* Estrela K1,4: centro 0 e quatro folhas, nao ha nem caminho nem ciclo. */
    Grafo *estrela = grafo_criar(5);

    if (casa == NULL || pendente == NULL || estrela == NULL) {
        fprintf(stderr, "Erro ao criar os grafos.\n");
        grafo_destruir(casa);
        grafo_destruir(pendente);
        grafo_destruir(estrela);
        return;
    }

    grafo_adicionar_aresta(casa, 0, 1);
    grafo_adicionar_aresta(casa, 1, 2);
    grafo_adicionar_aresta(casa, 2, 3);
    grafo_adicionar_aresta(casa, 3, 0);
    grafo_adicionar_aresta(casa, 0, 4);
    grafo_adicionar_aresta(casa, 1, 4);

    grafo_adicionar_aresta(pendente, 4, 0);
    grafo_adicionar_aresta(pendente, 0, 1);
    grafo_adicionar_aresta(pendente, 1, 2);
    grafo_adicionar_aresta(pendente, 2, 3);
    grafo_adicionar_aresta(pendente, 1, 3);

    for (int folha = 1; folha < 5; folha++) {
        grafo_adicionar_aresta(estrela, 0, folha);
    }

    testar_hamiltoniano("Grafo A (casa: C4 + telhado)", casa);
    testar_hamiltoniano("Grafo B (vertice 4 com grau 1)", pendente);
    testar_hamiltoniano("Grafo C (estrela K1,4)", estrela);

    grafo_destruir(casa);
    grafo_destruir(pendente);
    grafo_destruir(estrela);
}

static void parte_tsp(void) {
    const int tamanhos[] = {5, 8, 10, 12};
    const int qtd = (int)(sizeof(tamanhos) / sizeof(tamanhos[0]));

    printf("2. Experimento TSP: forca bruta x heuristicas\n");
    printf("Grafos completos com pesos aleatorios em [1, %d], semente %u\n\n",
           PESO_MAXIMO, SEMENTE);

    printf("+----+-------------------+-------------------+-------------------+\n");
    printf("|    |   Forca bruta     | Vizinho + proximo |  Insercao (+prox) |\n");
    printf("| n  |  custo | tempo ms |  custo | tempo ms |  custo | tempo ms |\n");
    printf("+----+--------+----------+--------+----------+--------+----------+\n");

    for (int i = 0; i < qtd; i++) {
        int n = tamanhos[i];
        InstanciaTSP *t = tsp_aleatorio(n, PESO_MAXIMO, SEMENTE + (unsigned)n);
        int *rota = malloc((size_t)n * sizeof(int));

        if (t == NULL || rota == NULL) {
            fprintf(stderr, "Erro de memoria para n = %d.\n", n);
            tsp_destruir(t);
            free(rota);
            return;
        }

        int c_fb = 0;
        int c_vmp = 0;
        int c_ins = 0;
        double t_fb = medir_ms(tsp_forca_bruta, t, rota, &c_fb);
        double t_vmp = medir_ms(tsp_vizinho_mais_proximo, t, rota, &c_vmp);
        double t_ins = medir_ms(tsp_insercao, t, rota, &c_ins);

        printf("| %2d | %6d | %8.3f | %6d | %8.4f | %6d | %8.4f |\n",
               n, c_fb, t_fb, c_vmp, t_vmp, c_ins, t_ins);

        tsp_destruir(t);
        free(rota);
    }

    printf("+----+--------+----------+--------+----------+--------+----------+\n");
}

int main(void) {
    printf("========================================\n");
    printf("  PRATICA 10 - HAMILTONIANO E TSP\n");
    printf("========================================\n\n");

    parte_hamiltoniano();
    parte_tsp();

    return 0;
}
