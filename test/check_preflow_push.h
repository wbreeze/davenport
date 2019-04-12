#ifndef CHECK_PREFLOW_PUSH_H
#define CHECK_PREFLOW_PUSH_H

Suite *make_preflow_push_suite(void);

// declare internal methods from preflow_push, for testing
void push(const int * capacity, int * flow, int *excess, int node_ct,
  int u, int v);
void relabel(const int * capacity, const int * flow, int *label,
  int node_ct, int from);

#endif
