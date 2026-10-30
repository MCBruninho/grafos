#include <stdio.h>
#include "agm.h"

int main()
{
    // grafo de grafo.dot (A=0, B=1, C=2, D=3, E=4, F=5)
    GrafoListaPonderado *grafo = criar_grafo(6);

    adicionar_aresta(grafo, 0, 1, 4);  // A - B
    adicionar_aresta(grafo, 0, 2, 2);  // A - C
    adicionar_aresta(grafo, 1, 2, 1);  // B - C
    adicionar_aresta(grafo, 1, 3, 5);  // B - D
    adicionar_aresta(grafo, 1, 4, 8);  // B - E
    adicionar_aresta(grafo, 2, 3, 4);  // C - D
    adicionar_aresta(grafo, 2, 4, 10); // C - E
    adicionar_aresta(grafo, 3, 4, 2);  // D - E
    adicionar_aresta(grafo, 3, 5, 1);  // D - F
    adicionar_aresta(grafo, 4, 5, 3);  // E - F

    printf("Grafo ponderado\n");
    imprimir_grafo(grafo);

    Aresta agm[5];
    int total = kruskal(grafo, agm);

    printf("Kruskal\n");
    for (int i = 0; i < grafo->num_vertices - 1; i++)
    {
        printf("%c - %c (%i)\n", 'A' + agm[i].u, 'A' + agm[i].v, agm[i].peso);
    }
    printf("Peso total = %i\n\n", total);

    int pred[6];
    total = prim(grafo, 0, pred);

    printf("Prim a partir de A\n");
    for (int v = 0; v < grafo->num_vertices; v++)
    {
        if (pred[v] != -1)
            printf("%c - %c\n", 'A' + pred[v], 'A' + v);
    }
    printf("Peso total = %i\n", total);

    return 0;
}