#ifndef COLORACAO_H
#define COLORACAO_H

typedef struct NoAdj {
    int vertice;
    struct NoAdj *prox;
} NoAdj;

typedef struct {
    int num_vertices;
    NoAdj **adj;
} GrafoLista;

GrafoLista *grafo_criar(int num_vertices);
void grafo_adicionar_aresta(GrafoLista *g, int origem, int destino);
void grafo_destruir(GrafoLista *g);

int *coloracao_gulosa(GrafoLista *g, int *num_cores);

int *coloracao_welsh_powell(GrafoLista *g, int *num_cores);

int eh_bipartido(GrafoLista *g);

#endif