#ifndef DAG_H
#define DAG_H

/* Pratica 03 - Ordenacao topologica em DAGs (Kahn e DFS).
   O grafo aqui e DIRECIONADO: a aresta (u, v) significa "u vem antes de v". */

typedef struct No
{
    int vertice;
    struct No *proximo;
} No;

typedef struct {
    No **lista;
    int num_vertices;
} GrafoLista;

/* --- Construcao do digrafo --- */
GrafoLista *criar_grafo(int n);
void adicionar_aresta(GrafoLista *g, int u, int v); /* aresta direcionada u -> v */
void liberar_grafo(GrafoLista *g);
void imprimir_grafo(GrafoLista *g);

/* Preenche grau_entrada[v] com o numero de arestas que chegam em v. */
void calcular_graus_entrada(GrafoLista *g, int *grau_entrada);

/* --- Ordenacao topologica --- */

/* Algoritmo de Kahn (BFS com grau de entrada).
   Retorna um array de n vertices em ordem topologica (deve ser liberado com free)
   ou NULL se o grafo possuir ciclo. *tamanho recebe o numero de vertices ordenados
   (0 quando ha ciclo). */
int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);

/* Variante DFS: empilha o vertice na SAIDA da recursao e devolve a pilha invertida.
   Retorna NULL se encontrar uma aresta de retorno (ciclo). */
int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);

/* Retorna 1 se o grafo e aciclico (DAG) e 0 caso contrario. */
int eh_dag(GrafoLista *g);

#endif
