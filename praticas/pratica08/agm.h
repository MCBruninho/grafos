#ifndef AGM_H
#define AGM_H

#define INFINITO 1000000000

typedef struct No
{
    int vertice;
    int peso;
    struct No *proximo;
} No;

typedef struct
{
    No **lista;
    int num_vertices;
} GrafoListaPonderado;

typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

typedef struct {
    int vertice;
    int chave;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

GrafoListaPonderado *criar_grafo(int n);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int p);
void imprimir_grafo(GrafoListaPonderado *g);

DSU *criar_dsu(int n);
int find(DSU *d, int x);
// Retorna 1 se juntou dois conjuntos ou 0 se x e y já estavam juntos.
int unir(DSU *d, int x, int y);

MinHeap *criar_min_heap(int capacidade);
void inserir(MinHeap *h, int vertice, int chave);
NoHeap extrair_minimo(MinHeap *h);
void diminuir_chave(MinHeap *h, int vertice, int chave);

// Preenche agm[] com as n-1 arestas escolhidas e retorna o peso total.
int kruskal(GrafoListaPonderado *g, Aresta *agm);

// Preenche pred[] (pai de cada vértice na árvore) e retorna o peso total.
int prim(GrafoListaPonderado *g, int origem, int *pred);

#endif