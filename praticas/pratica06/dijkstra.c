#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

GrafoListaPonderado *criar_grafo(int n)
{
    GrafoListaPonderado *g = (GrafoListaPonderado *)malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = n;
    g->lista = (No **)malloc(sizeof(No *) * n);
    for (int i = 0; i < n; i++)
    {
        g->lista[i] = NULL;
    }
    return g;
}

void adicionar_arco(GrafoListaPonderado *g, int u, int v, int p)
{
    // u -> v
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->peso = p;
    no->proximo = g->lista[u];
    g->lista[u] = no;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int p)
{
    adicionar_arco(g, u, v, p);
    adicionar_arco(g, v, u, p);
}

void imprimir_grafo(GrafoListaPonderado *g)
{
    printf("\n");
    for (int i = 0; i < g->num_vertices; i++)
    {
        printf("%c: -> ", 'A' + i);
        No *no = g->lista[i];
        while (no != NULL)
        {
            printf("(%c, %i) -> ", 'A' + no->vertice, no->peso);
            no = no->proximo;
        }
        printf("NULL\n");
    }
    printf("\n");
}

MinHeap *criar_min_heap(int capacidade)
{
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    h->dados = (NoHeap *)malloc(sizeof(NoHeap) * capacidade);
    h->posicao = (int *)malloc(sizeof(int) * capacidade);
    h->capacidade = capacidade;
    h->tamanho = 0;
    return h;
}

// troca dois nós do heap e atualiza a posição de cada vértice
void trocar(MinHeap *h, int i, int j)
{
    NoHeap aux = h->dados[i];
    h->dados[i] = h->dados[j];
    h->dados[j] = aux;

    h->posicao[h->dados[i].vertice] = i;
    h->posicao[h->dados[j].vertice] = j;
}

// sobe o nó i enquanto ele for menor que o pai
void subir(MinHeap *h, int i)
{
    while (i > 0 && h->dados[i].distancia < h->dados[(i - 1) / 2].distancia)
    {
        trocar(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// desce o nó i enquanto algum filho for menor que ele
void descer(MinHeap *h, int i)
{
    while (1)
    {
        int menor = i;
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;

        if (esq < h->tamanho && h->dados[esq].distancia < h->dados[menor].distancia)
            menor = esq;
        if (dir < h->tamanho && h->dados[dir].distancia < h->dados[menor].distancia)
            menor = dir;

        if (menor == i)
            return;

        trocar(h, i, menor);
        i = menor;
    }
}

void inserir(MinHeap *h, int vertice, int distancia)
{
    int i = h->tamanho++;
    h->dados[i].vertice = vertice;
    h->dados[i].distancia = distancia;
    h->posicao[vertice] = i;
    subir(h, i);
}

// tira a raiz, coloca o último nó no lugar dela e desce
NoHeap extrair_minimo(MinHeap *h)
{
    NoHeap minimo = h->dados[0];
    trocar(h, 0, h->tamanho - 1);
    h->tamanho--;
    h->posicao[minimo.vertice] = -1; // saiu do heap
    descer(h, 0);
    return minimo;
}

// posicao[] diz onde o vértice está, então basta subir a partir dali: O(log V)
void diminuir_chave(MinHeap *h, int vertice, int distancia)
{
    int i = h->posicao[vertice];
    h->dados[i].distancia = distancia;
    subir(h, i);
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred)
{
    MinHeap *h = criar_min_heap(g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++)
    {
        dist[i] = INFINITO;
        pred[i] = -1;
    }
    dist[origem] = 0;

    for (int i = 0; i < g->num_vertices; i++)
    {
        inserir(h, i, dist[i]);
    }

    // a cada passo o vértice mais próximo ainda no heap tem distância definitiva
    while (h->tamanho > 0)
    {
        int u = extrair_minimo(h).vertice;
        if (dist[u] == INFINITO)
            break; // o restante não é alcançável a partir da origem

        No *no = g->lista[u];
        while (no != NULL)
        {
            int v = no->vertice;
            // relaxa a aresta u -> v
            if (h->posicao[v] != -1 && dist[u] + no->peso < dist[v])
            {
                dist[v] = dist[u] + no->peso;
                pred[v] = u;
                diminuir_chave(h, v, dist[v]);
            }
            no = no->proximo;
        }
    }

    free(h->dados);
    free(h->posicao);
    free(h);
}

// volta pelo pred[] até a origem e imprime o caminho na ida
void reconstruir_caminho(int origem, int destino, int *pred)
{
    if (destino == origem)
    {
        printf("%c", 'A' + origem);
        return;
    }
    if (pred[destino] == -1)
    {
        printf("sem caminho");
        return;
    }
    reconstruir_caminho(origem, pred[destino], pred);
    printf(" -> %c", 'A' + destino);
}