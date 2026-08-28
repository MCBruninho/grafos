#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main(void) {
    printf("=== Grafo com Matriz de Adjacencia ===\n");
    GrafoMatriz *gm = criar_grafo_matriz(5);
    inserir_aresta_matriz(gm, 0, 1);
    inserir_aresta_matriz(gm, 0, 2);
    inserir_aresta_matriz(gm, 1, 2);
    inserir_aresta_matriz(gm, 3, 4);
    imprimir_grafo_matriz(gm);
    printf("Grau(0)=  %d | Adjacentes(0,1) = %d\n", grau_matriz(gm, 0), sao_adjacentes_matriz(gm, 0, 1));

    remover_aresta_matriz(gm, 0, 1);
    printf("\nApos remover aresta 0-1:\n");
    imprimir_grafo_matriz(gm);
    printf("Grau(0) = %d | Adjacentes(0,1) = %d\n", grau_matriz(gm, 0), sao_adjacentes_matriz(gm, 0, 1));
    liberar_grafo_matriz(gm);

    printf("\n=== Grafo com Lista de Adjacencia ===\n");
    GrafoLista *gl = criar_grafo_lista(5);
    inserir_aresta_lista(gl, 0, 1);
    inserir_aresta_lista(gl, 0, 2);
    inserir_aresta_lista(gl, 1, 2);
    inserir_aresta_lista(gl, 3, 4);
    imprimir_grafo_lista(gl);
    printf("Grau(0) = %d | Adjacentes(0,1) = %d\n", grau_lista(gl, 0), sao_adjacentes_lista(gl, 0, 1));

    remover_aresta_lista(gl, 0, 1);
    printf("\nApos remover aresta 0-1:\n");
    imprimir_grafo_lista(gl);
    printf("Grau(0) = %d | Adjacentes(0,1) = %d\n", grau_lista(gl, 0), sao_adjacentes_lista(gl, 0, 1));
    liberar_grafo_lista(gl);

    return 0;
}