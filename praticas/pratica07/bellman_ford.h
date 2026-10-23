#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

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

GrafoListaPonderado *criar_grafo(int n);
void adicionar_arco(GrafoListaPonderado *g, int u, int v, int p);
void imprimir_grafo(GrafoListaPonderado *g);

// Retorna 1 se calculou as distâncias ou 0 se existe ciclo negativo.
int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);

// Usa dist[] e pred[] deixados pelo bellman_ford para imprimir o ciclo.
void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred);

#endif