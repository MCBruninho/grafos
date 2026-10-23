#include "grafo_lista.h"

#ifndef BUSCA_PROFUNDIDADE
#define BUSCA_PROFUNDIDADE

/* Pilha (LIFO) usada pela DFS iterativa. */
typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

Pilha *criar_pilha(int capacidade);
int pilha_vazia(Pilha *p);
void empilhar(Pilha *p, int v);
int desempilhar(Pilha *p);
void liberar_pilha(Pilha *p);

/* DFS recursiva (a pilha e a propria pilha de chamadas).
   visitado[v] = 1 quando v ja foi descoberto
   pred[v]     = vertice que descobriu v (-1 para a raiz)
   ordem[]     = vertices na ordem de visita, com *n_ordem elementos */
void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred, int *ordem, int *n_ordem);

/* Mesma varredura, trocando a recursao por uma Pilha explicita. */
void dfs_iterativa(GrafoLista *g, int origem, int *visitado, int *pred, int *ordem, int *n_ordem);

int tem_ciclo(GrafoLista *g);

#endif
