#include <stdio.h>
#include "bellman_ford.h"

int main()
{
    // digrafo com pesos negativos, mas sem ciclo negativo
    GrafoListaPonderado *digrafo = criar_grafo(5);

    adicionar_arco(digrafo, 0, 1, 6);
    adicionar_arco(digrafo, 0, 2, 7);
    adicionar_arco(digrafo, 1, 2, 8);
    adicionar_arco(digrafo, 1, 3, 5);
    adicionar_arco(digrafo, 1, 4, -4);
    adicionar_arco(digrafo, 2, 3, -3);
    adicionar_arco(digrafo, 2, 4, 9);
    adicionar_arco(digrafo, 3, 1, -2);
    adicionar_arco(digrafo, 4, 3, 7);

    printf("Digrafo com pesos negativos\n");
    imprimir_grafo(digrafo);

    int dist[5];
    int pred[5];
    if (bellman_ford(digrafo, 0, dist, pred))
    {
        printf("Bellman-Ford a partir de A\n");
        for (int v = 0; v < digrafo->num_vertices; v++)
        {
            printf("A ate %c: distancia %i (predecessor ", 'A' + v, dist[v]);
            if (pred[v] == -1)
                printf("-)\n");
            else
                printf("%c)\n", 'A' + pred[v]);
        }
    }
    else
    {
        reconstruir_ciclo_negativo(digrafo, dist, pred);
    }
    printf("\n");

    // digrafo com o ciclo negativo B -> C -> D -> B (1 - 3 + 1 = -1)
    GrafoListaPonderado *com_ciclo = criar_grafo(5);

    adicionar_arco(com_ciclo, 0, 1, 4);
    adicionar_arco(com_ciclo, 1, 2, 1);
    adicionar_arco(com_ciclo, 2, 3, -3);
    adicionar_arco(com_ciclo, 3, 1, 1);
    adicionar_arco(com_ciclo, 3, 4, 2);

    printf("Digrafo com ciclo negativo\n");
    imprimir_grafo(com_ciclo);

    int dist2[5];
    int pred2[5];
    if (bellman_ford(com_ciclo, 0, dist2, pred2))
    {
        printf("Nenhum ciclo negativo\n");
    }
    else
    {
        reconstruir_ciclo_negativo(com_ciclo, dist2, pred2);
    }

    return 0;
}