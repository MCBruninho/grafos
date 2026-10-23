#include <stdio.h>
#include "dijkstra.h"

int main()
{
    GrafoListaPonderado *digrafo = criar_grafo(4);

    adicionar_arco(digrafo, 0, 1, 4);
    adicionar_arco(digrafo, 0, 2, 1);
    adicionar_arco(digrafo, 1, 3, 1);
    adicionar_arco(digrafo, 2, 1, 2);
    adicionar_arco(digrafo, 2, 3, 5);

    printf("Digrafo ponderado\n");
    imprimir_grafo(digrafo);

    int dist[4];
    int pred[4];
    dijkstra(digrafo, 0, dist, pred);

    printf("Dijkstra a partir de A\n");
    for (int v = 0; v < digrafo->num_vertices; v++)
    {
        printf("A ate %c: distancia %i, caminho ", 'A' + v, dist[v]);
        reconstruir_caminho(0, v, pred);
        printf("\n");
    }
    printf("\n");

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

    printf("Grafo ponderado nao orientado\n");
    imprimir_grafo(grafo);

    int dist2[6];
    int pred2[6];
    dijkstra(grafo, 0, dist2, pred2);

    printf("Dijkstra a partir de A\n");
    for (int v = 0; v < grafo->num_vertices; v++)
    {
        printf("A ate %c: distancia %i, caminho ", 'A' + v, dist2[v]);
        reconstruir_caminho(0, v, pred2);
        printf("\n");
    }
    printf("\n");

    GrafoListaPonderado *desconexo = criar_grafo(3);
    adicionar_aresta(desconexo, 0, 1, 2);

    int dist3[3];
    int pred3[3];
    dijkstra(desconexo, 0, dist3, pred3);

    printf("Grafo desconexo\n");
    printf("A ate C: ");
    reconstruir_caminho(0, 2, pred3);
    printf("\n");

    return 0;
}