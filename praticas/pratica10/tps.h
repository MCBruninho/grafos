#ifndef TPS_H
#define TPS_H

#include "hamiltoniano.h"

/*
 * Instancia do Problema do Caixeiro Viajante (TSP) simetrico:
 * grafo completo com distancia dist[u][v] == dist[v][u].
 */
typedef struct {
    int n;
    int **dist;
} InstanciaTSP;

InstanciaTSP *tsp_criar(int n);
void tsp_destruir(InstanciaTSP *t);

/* Instancia aleatoria com distancias inteiras em [1, peso_maximo]. */
InstanciaTSP *tsp_aleatorio(int n, int peso_maximo, unsigned semente);

/* Custo do ciclo rota[0] -> ... -> rota[n-1] -> rota[0]. */
int tsp_custo_rota(const InstanciaTSP *t, const int *rota);

/*
 * As funcoes abaixo preenchem 'rota' (n posicoes, comecando no vertice 0;
 * o retorno a 0 fica implicito) e retornam o custo do ciclo, ou -1 em erro.
 */

/* Exato: fixa a origem 0 e gera todas as (n-1)! permutacoes do resto. */
int tsp_forca_bruta(const InstanciaTSP *t, int *rota);

/* Heuristica construtiva: sempre vai para a cidade nao visitada mais proxima. */
int tsp_vizinho_mais_proximo(const InstanciaTSP *t, int *rota);

/*
 * Heuristica de insercao do mais proximo: escolhe a cidade fora do ciclo
 * mais proxima de alguma cidade do ciclo e a insere na posicao que menos
 * aumenta o custo.
 */
int tsp_insercao(const InstanciaTSP *t, int *rota);

/*
 * Reducao Ciclo Hamiltoniano -> TSP: peso 1 para arestas existentes em g
 * e 2 para as inexistentes. g tem ciclo Hamiltoniano se e somente se o
 * custo otimo do TSP gerado for exatamente n.
 */
InstanciaTSP *grafo_para_tsp(const Grafo *g);

#endif
