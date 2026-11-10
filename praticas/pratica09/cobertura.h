#ifndef COBERTURA_H
#define COBERTURA_H

/*
 * Grafo nao direcionado representado por matriz de adjacencia.
 * adj[u][v] == 1 indica que existe a aresta {u, v}.
 */
typedef struct {
    int num_vertices;
    int num_arestas;
    int **adj;
} Grafo;

Grafo *grafo_criar(int num_vertices);
void grafo_adicionar_aresta(Grafo *g, int u, int v);
void grafo_destruir(Grafo *g);

/* Gera um grafo aleatorio G(n, p) com semente fixa (reprodutivel). */
Grafo *grafo_aleatorio(int num_vertices, double probabilidade, unsigned semente);

/*
 * Vetores de cobertura: cobertura[v] == 1 se o vertice v esta na cobertura,
 * 0 caso contrario. O vetor deve ter num_vertices posicoes.
 */

/* Retorna 1 se todas as arestas possuem ao menos uma ponta na cobertura. */
int eh_cobertura(const Grafo *g, const int *cobertura);

/*
 * Cobertura minima exata por backtracking com poda por limite
 * (branch and bound). Preenche 'cobertura' e retorna seu tamanho,
 * ou -1 em caso de erro.
 */
int cobertura_minima_bt(const Grafo *g, int *cobertura);

/*
 * Heuristica gulosa: escolhe repetidamente o vertice de maior grau
 * restante (arestas ainda nao cobertas). Preenche 'cobertura' e retorna
 * seu tamanho, ou -1 em caso de erro.
 */
int cobertura_gulosa(const Grafo *g, int *cobertura);

#endif
