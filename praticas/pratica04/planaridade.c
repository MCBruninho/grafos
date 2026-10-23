#include <stdio.h>
#include <stdlib.h>
#include "planaridade.h"

/* ========================= Formula de Euler ========================= */

int eh_planar_euler(GrafoLista *g) {
    int n = g->num_vertices;
    int m = contar_arestas(g);

    /* com menos de 3 vertices qualquer grafo simples e planar */
    if (n < 3) {
        return 1;
    }
    return m <= 3 * n - 6;
}

/* ========================= Busca de subdivisoes (forca bruta) =========================

   Uma subdivisao de H aparece no grafo quando escolhemos vertices de ramificacao
   (um para cada vertice de H) e ligamos os pares exigidos por H com caminhos que
   nao compartilham vertices internos nem passam por outro vertice de ramificacao.
   O array ocupado[] guarda exatamente isso: comeca marcando os ramos e vai marcando
   os vertices internos ja consumidos, desmarcando no backtracking. */

typedef struct {
    GrafoLista *g;
    Aresta *pares;
    int num_pares;
    int *ocupado;
} Busca;

static int conectar(Busca *b, int indice);

/* Enumera caminhos de 'atual' ate 'destino' e, a cada caminho completo, tenta
   resolver o proximo par; se nao der, continua procurando outra rota. */
static int caminho(Busca *b, int atual, int destino, int indice) {
    for (No *no = b->g->lista[atual]; no != NULL; no = no->proximo) {
        int v = no->vertice;

        if (v == destino) {
            if (conectar(b, indice + 1)) {
                return 1;
            }
        } else if (!b->ocupado[v]) {
            b->ocupado[v] = 1;
            if (caminho(b, v, destino, indice)) {
                return 1;
            }
            b->ocupado[v] = 0;
        }
    }
    return 0;
}

static int conectar(Busca *b, int indice) {
    if (indice == b->num_pares) {
        return 1; /* todos os pares ligados: a subdivisao existe */
    }
    return caminho(b, b->pares[indice].u, b->pares[indice].v, indice);
}

/* Prepara a busca com os vertices de ramificacao ja marcados como ocupados. */
static int existe_subdivisao(GrafoLista *g, int *ramos, int num_ramos,
                             Aresta *pares, int num_pares) {
    Busca b;
    int encontrou;

    b.g = g;
    b.pares = pares;
    b.num_pares = num_pares;
    b.ocupado = (int *)calloc(g->num_vertices, sizeof(int));

    for (int i = 0; i < num_ramos; i++) {
        b.ocupado[ramos[i]] = 1;
    }

    encontrou = conectar(&b, 0);

    free(b.ocupado);
    return encontrou;
}

/* ========================= K5 ========================= */

static int testar_k5(GrafoLista *g, int *ramos) {
    Aresta pares[10];
    int total = 0;

    /* K5: todos os 10 pares entre os 5 vertices de ramificacao */
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            pares[total].u = ramos[i];
            pares[total].v = ramos[j];
            total++;
        }
    }
    return existe_subdivisao(g, ramos, 5, pares, total);
}

static int combinar_k5(GrafoLista *g, int *ramos, int escolhidos, int inicio) {
    if (escolhidos == 5) {
        return testar_k5(g, ramos);
    }
    for (int v = inicio; v < g->num_vertices; v++) {
        /* no K5 cada vertice de ramificacao precisa de 4 caminhos saindo dele */
        if (grau(g, v) < 4) {
            continue;
        }
        ramos[escolhidos] = v;
        if (combinar_k5(g, ramos, escolhidos + 1, v + 1)) {
            return 1;
        }
    }
    return 0;
}

int contem_subdivisao_k5(GrafoLista *g) {
    int ramos[5];

    if (g->num_vertices < 5) {
        return 0;
    }
    return combinar_k5(g, ramos, 0, 0);
}

/* ========================= K3,3 ========================= */

static int testar_k33(GrafoLista *g, int *seis) {
    Aresta pares[9];

    /* o primeiro vertice fica fixo no lado A para nao repetir particoes simetricas */
    for (int i = 1; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            int a[3] = { seis[0], seis[i], seis[j] };
            int b[3];
            int k = 0;
            int total = 0;

            for (int t = 1; t < 6; t++) {
                if (t != i && t != j) {
                    b[k++] = seis[t];
                }
            }

            /* K3,3: cada vertice de A se liga aos 3 vertices de B */
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    pares[total].u = a[x];
                    pares[total].v = b[y];
                    total++;
                }
            }

            if (existe_subdivisao(g, seis, 6, pares, total)) {
                return 1;
            }
        }
    }
    return 0;
}

static int combinar_k33(GrafoLista *g, int *ramos, int escolhidos, int inicio) {
    if (escolhidos == 6) {
        return testar_k33(g, ramos);
    }
    for (int v = inicio; v < g->num_vertices; v++) {
        /* no K3,3 cada vertice de ramificacao precisa de 3 caminhos saindo dele */
        if (grau(g, v) < 3) {
            continue;
        }
        ramos[escolhidos] = v;
        if (combinar_k33(g, ramos, escolhidos + 1, v + 1)) {
            return 1;
        }
    }
    return 0;
}

int contem_subdivisao_k33(GrafoLista *g) {
    int ramos[6];

    if (g->num_vertices < 6) {
        return 0;
    }
    return combinar_k33(g, ramos, 0, 0);
}

/* ========================= Resultado final ========================= */

int eh_planar_kuratowski(GrafoLista *g) {
    if (g->num_vertices > 10) {
        return -1; /* forca bruta so e viavel para n <= 10 */
    }
    if (contem_subdivisao_k5(g) || contem_subdivisao_k33(g)) {
        return 0;
    }
    return 1;
}

int verificar_planaridade(GrafoLista *g) {
    if (!eh_planar_euler(g)) {
        return 0; /* violar m <= 3n - 6 ja e prova de que nao e planar */
    }
    return eh_planar_kuratowski(g);
}
