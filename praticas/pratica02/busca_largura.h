#include "grafo_lista.h"

#ifndef BUSCA_LARGURA
#define BUSCA_LARGURA

/* Fila (FIFO) circular usada pela BFS. */
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

Fila *criar_fila(int capacidade);
int fila_vazia(Fila *f);
void enfileirar(Fila *f, int v);
int desenfileirar(Fila *f);
void liberar_fila(Fila *f);

/* Busca em largura a partir de origem.
   dist[v] = numero de arestas de origem ate v (-1 se inalcancavel)
   pred[v] = vertice anterior a v na arvore de busca (-1 se nao tem) */
void bfs(GrafoLista *g, int origem, int *dist, int *pred);

void imprimir_caminho(int *pred, int destino);
int contar_componentes(GrafoLista *g);
int eh_bipartido(GrafoLista *g);

#endif
