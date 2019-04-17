#ifndef TEST_PREFLOW_PUSH_H
#define TEST_PREFLOW_PUSH_H

// declare internal methods from preflow_push, for testing
void push(const int *capacity, int *flow, int *excess, int node_ct,
  int u, int v);
void relabel(const int *capacity, const int *flow, int *labels,
  int node_ct, int u);
void discharge(const int *capacity, int *flow, int *excess, int *labels,
  int *seen, int node_ct, int u);
void saturate_from_source(const int *capacity, int *flow, int *excess,
  int node_ct, int u);
void initialize_list(int *list, int node_ct, int source, int sink);

#endif
