#ifndef DIJKSTRA_H
#define DIJKSTRA_H

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
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

GrafoListaPonderado *criar_grafo(int n);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int p);
void adicionar_arco(GrafoListaPonderado *g, int u, int v, int p);
void imprimir_grafo(GrafoListaPonderado *g);

MinHeap *criar_min_heap(int capacidade);
void inserir(MinHeap *h, int vertice, int distancia);
NoHeap extrair_minimo(MinHeap *h);
void diminuir_chave(MinHeap *h, int vertice, int distancia);

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif