#ifndef PLANARIDADE_H
#define PLANARIDADE_H

#include "conectividade.h"

/* Pratica 04 - Verificacao de planaridade por Euler + heuristica de Kuratowski. */

/* Formula de Euler para grafos simples e conexos com n >= 3: m <= 3n - 6.
   E uma condicao NECESSARIA, nao suficiente: se falhar o grafo com certeza nao e
   planar, mas passar no teste nao garante planaridade (o K3,3 passa e nao e planar).
   Retorna 1 se o grafo satisfaz o limite e 0 caso contrario. */
int eh_planar_euler(GrafoLista *g);

/* Teorema de Kuratowski: um grafo e planar se, e somente se, nao contem subdivisao
   de K5 nem de K3,3. As duas funcoes abaixo procuram essas subdivisoes por forca
   bruta (viavel para n <= 10): escolhem os vertices de ramificacao e tentam ligar
   cada par exigido por caminhos internamente disjuntos. */
int contem_subdivisao_k5(GrafoLista *g);
int contem_subdivisao_k33(GrafoLista *g);

/* Retorna 1 (planar), 0 (nao planar) ou -1 quando n > 10, caso em que a forca bruta
   nao e aplicada. */
int eh_planar_kuratowski(GrafoLista *g);

/* Combina os dois testes: reprova direto quem falha em Euler e, se n <= 10, confirma
   o resultado com Kuratowski. Retorna 1, 0 ou -1 (indeterminado). */
int verificar_planaridade(GrafoLista *g);

#endif
