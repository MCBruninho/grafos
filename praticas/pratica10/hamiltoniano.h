#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

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
 * Caminho Hamiltoniano por forca bruta (backtracking sobre permutacoes):
 * tenta cada vertice como inicio e estende o caminho com vizinhos ainda
 * nao visitados, desfazendo a escolha quando chega a um beco sem saida.
 *
 * 'caminho' deve ter num_vertices posicoes. Retorna 1 se encontrou
 * (e preenche 'caminho'), 0 caso contrario.
 */
int encontrar_caminho_hamiltoniano_bt(const Grafo *g, int *caminho);

/*
 * Ciclo Hamiltoniano por forca bruta: fixa o vertice 0 como inicio
 * (todo ciclo passa por ele) e exige aresta do ultimo vertice de volta a 0.
 *
 * 'ciclo' deve ter num_vertices posicoes (o retorno a 0 fica implicito).
 * Retorna 1 se encontrou, 0 caso contrario.
 */
int encontrar_ciclo_hamiltoniano_bt(const Grafo *g, int *ciclo);

#endif
