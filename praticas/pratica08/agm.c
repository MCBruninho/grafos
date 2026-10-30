#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

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

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int p)
{
    // u -> v
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->peso = p;
    no->proximo = g->lista[u];
    g->lista[u] = no;

    // v -> u
    no = (No *)malloc(sizeof(No));
    no->vertice = u;
    no->peso = p;
    no->proximo = g->lista[v];
    g->lista[v] = no;
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

DSU *criar_dsu(int n)
{
    DSU *d = (DSU *)malloc(sizeof(DSU));
    d->pai = (int *)malloc(sizeof(int) * n);
    d->rank = (int *)malloc(sizeof(int) * n);
    d->n = n;
    // cada vértice começa sozinho no seu conjunto
    for (int i = 0; i < n; i++)
    {
        d->pai[i] = i;
        d->rank[i] = 0;
    }
    return d;
}

// compressão de caminho: todos no caminho passam a apontar direto para a raiz
int find(DSU *d, int x)
{
    if (d->pai[x] != x)
        d->pai[x] = find(d, d->pai[x]);
    return d->pai[x];
}

// união por rank: a árvore mais baixa fica embaixo da mais alta
int unir(DSU *d, int x, int y)
{
    int rx = find(d, x);
    int ry = find(d, y);
    if (rx == ry)
        return 0;

    if (d->rank[rx] < d->rank[ry])
    {
        d->pai[rx] = ry;
    }
    else if (d->rank[rx] > d->rank[ry])
    {
        d->pai[ry] = rx;
    }
    else
    {
        d->pai[ry] = rx;
        d->rank[rx]++;
    }
    return 1;
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
    while (i > 0 && h->dados[i].chave < h->dados[(i - 1) / 2].chave)
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

        if (esq < h->tamanho && h->dados[esq].chave < h->dados[menor].chave)
            menor = esq;
        if (dir < h->tamanho && h->dados[dir].chave < h->dados[menor].chave)
            menor = dir;

        if (menor == i)
            return;

        trocar(h, i, menor);
        i = menor;
    }
}

void inserir(MinHeap *h, int vertice, int chave)
{
    int i = h->tamanho++;
    h->dados[i].vertice = vertice;
    h->dados[i].chave = chave;
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

void diminuir_chave(MinHeap *h, int vertice, int chave)
{
    int i = h->posicao[vertice];
    h->dados[i].chave = chave;
    subir(h, i);
}

int comparar_arestas(const void *a, const void *b)
{
    return ((Aresta *)a)->peso - ((Aresta *)b)->peso;
}

int kruskal(GrafoListaPonderado *g, Aresta *agm)
{
    int n = g->num_vertices;

    // monta a lista de arestas (cada aresta aparece duas vezes na lista de
    // adjacência, então só guarda quando u < v)
    int m = 0;
    for (int u = 0; u < n; u++)
    {
        for (No *no = g->lista[u]; no != NULL; no = no->proximo)
        {
            if (u < no->vertice)
                m++;
        }
    }

    Aresta arestas[m];
    int k = 0;
    for (int u = 0; u < n; u++)
    {
        for (No *no = g->lista[u]; no != NULL; no = no->proximo)
        {
            if (u < no->vertice)
            {
                arestas[k].u = u;
                arestas[k].v = no->vertice;
                arestas[k].peso = no->peso;
                k++;
            }
        }
    }

    qsort(arestas, m, sizeof(Aresta), comparar_arestas);

    // pega as arestas da mais leve para a mais pesada, pulando as que
    // ligariam dois vértices que já estão na mesma árvore (formariam ciclo)
    DSU *d = criar_dsu(n);
    int total = 0;
    int escolhidas = 0;
    for (int i = 0; i < m && escolhidas < n - 1; i++)
    {
        if (unir(d, arestas[i].u, arestas[i].v))
        {
            agm[escolhidas++] = arestas[i];
            total += arestas[i].peso;
        }
    }

    free(d->pai);
    free(d->rank);
    free(d);
    return total;
}

int prim(GrafoListaPonderado *g, int origem, int *pred)
{
    int n = g->num_vertices;
    int chave[n]; // menor peso de aresta que liga o vértice à árvore
    MinHeap *h = criar_min_heap(n);

    for (int i = 0; i < n; i++)
    {
        chave[i] = INFINITO;
        pred[i] = -1;
    }
    chave[origem] = 0;

    for (int i = 0; i < n; i++)
    {
        inserir(h, i, chave[i]);
    }

    // a cada passo entra na árvore o vértice mais barato de alcançar
    int total = 0;
    while (h->tamanho > 0)
    {
        int u = extrair_minimo(h).vertice;
        total += chave[u];

        No *no = g->lista[u];
        while (no != NULL)
        {
            int v = no->vertice;
            if (h->posicao[v] != -1 && no->peso < chave[v])
            {
                chave[v] = no->peso;
                pred[v] = u;
                diminuir_chave(h, v, chave[v]);
            }
            no = no->proximo;
        }
    }

    free(h->dados);
    free(h->posicao);
    free(h);
    return total;
}