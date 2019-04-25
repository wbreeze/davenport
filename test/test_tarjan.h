#ifndef TEST_TARJAN_H
#define TEST_TARJAN_H

#include "../src/tarjan.h"

void tarjan_init(Tarjan *tarjan);
void tarjan_push(Tarjan *tarjan, int v);
int tarjan_pop(Tarjan *tarjan);
int tarjan_next_index(Tarjan *tarjan);

#endif
