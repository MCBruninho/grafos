#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H

/* Pratica 04 - Vertices de corte (articulacoes) e pontes via algoritmo de Tarjan.
   O grafo aqui e NAO DIRECIONADO: cada aresta {u, v} entra nas duas listas. */

typedef struct No
{
    int vertice;
    struct No *proximo;
} No;

typedef struct {
    No **lista;
    int num_vertices;
} GrafoLista;

/* Par de vertices usado para devolver as pontes encontradas. */
typedef struct {
    int u, v;
} Aresta;

/* --- Construcao do grafo --- */
GrafoLista *criar_grafo(int n);
void adicionar_aresta_nao_direcionada(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);
void imprimir_grafo(GrafoLista *g);

int contar_arestas(GrafoLista *g);
int grau(GrafoLista *g, int v);
int existe_aresta(GrafoLista *g, int u, int v);

/* --- Tarjan ---

   descoberta[u] = instante em que u foi descoberto pela DFS;
   low[u]        = menor instante alcancavel a partir da subarvore de u usando
                   no maximo uma aresta de retorno.

   Um vertice u e articulacao quando:
     - u e raiz da DFS e possui 2 ou mais filhos na arvore; ou
     - u nao e raiz e existe um filho v com low[v] >= descoberta[u].

   Uma aresta (u, v) da arvore e ponte quando low[v] > descoberta[u]. */

/* Passo recursivo de Tarjan: marca em eh_articulacao[] os vertices de corte
   alcancaveis a partir de u. Arrays devem ter tamanho g->num_vertices, com
   descoberta[] zerado, pai[] em -1 e *tempo comecando em 0. */
void dfs_articulacoes(GrafoLista *g, int u, int *descoberta, int *low, int *pai,
                      int *eh_articulacao, int *tempo);

/* Roda a DFS acima em todos os componentes e devolve um array com os vertices de
   corte (liberar com free) ou NULL se nao houver nenhum. */
int *encontrar_articulacoes(GrafoLista *g, int *quantidade);

/* Devolve um array com as pontes do grafo (liberar com free) ou NULL se nao houver
   nenhuma. Usa a condicao low[v] > descoberta[u]. */
Aresta *detectar_pontes(GrafoLista *g, int *quantidade);

#endif
