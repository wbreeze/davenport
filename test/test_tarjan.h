#ifndef TEST_TARJAN_H
#define TEST_TARJAN_H

#include "../src/tarjan.h"

Tarjan *tarjan_new(const int *edges, int node_ct, int *components);
Tarjan *tarjan_destroy(Tarjan *tarjan);
void tarjan_push(Tarjan *tarjan, int v);
int tarjan_pop(Tarjan *tarjan);
int tarjan_next_index(Tarjan *tarjan);

#endif
