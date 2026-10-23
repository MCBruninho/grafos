#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

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

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred)
{
    int n = g->num_vertices;

    for (int i = 0; i < n; i++)
    {
        dist[i] = INFINITO;
        pred[i] = -1;
    }
    dist[origem] = 0;

    // um caminho mínimo tem no máximo n-1 arestas: n-1 rodadas relaxando todas
    for (int i = 0; i < n - 1; i++)
    {
        for (int u = 0; u < n; u++)
        {
            if (dist[u] == INFINITO)
                continue;

            No *no = g->lista[u];
            while (no != NULL)
            {
                int v = no->vertice;
                if (dist[u] + no->peso < dist[v])
                {
                    dist[v] = dist[u] + no->peso;
                    pred[v] = u;
                }
                no = no->proximo;
            }
        }
    }

    // n-ésima rodada: se ainda dá para melhorar, existe ciclo negativo
    for (int u = 0; u < n; u++)
    {
        if (dist[u] == INFINITO)
            continue;

        No *no = g->lista[u];
        while (no != NULL)
        {
            if (dist[u] + no->peso < dist[no->vertice])
                return 0;
            no = no->proximo;
        }
    }

    return 1;
}

void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred)
{
    int n = g->num_vertices;

    // acha uma aresta u -> v que ainda relaxa e faz a última relaxação
    int x = -1;
    for (int u = 0; u < n && x == -1; u++)
    {
        if (dist[u] == INFINITO)
            continue;

        No *no = g->lista[u];
        while (no != NULL)
        {
            if (dist[u] + no->peso < dist[no->vertice])
            {
                x = no->vertice;
                pred[x] = u;
                break;
            }
            no = no->proximo;
        }
    }

    if (x == -1)
    {
        printf("Nenhum ciclo negativo encontrado\n");
        return;
    }

    // voltar n vezes pelo pred[] garante cair dentro do ciclo
    for (int i = 0; i < n; i++)
    {
        x = pred[x];
    }

    // anda pelo ciclo até voltar em x (sai ao contrário)
    int ciclo[n + 1];
    int tamanho = 0;
    int v = x;
    do
    {
        ciclo[tamanho++] = v;
        v = pred[v];
    } while (v != x);
    ciclo[tamanho++] = x;

    printf("Ciclo negativo: ");
    for (int i = tamanho - 1; i >= 0; i--)
    {
        printf("%c", 'A' + ciclo[i]);
        if (i > 0)
            printf(" -> ");
    }
    printf("\n");
}