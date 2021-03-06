#ifndef PREFLOW_PUSH
#define PREFLOW_PUSH

#include "network.h"

typedef struct PreflowPush PreflowPush;
PreflowPush *preflow_push_new(const int *capacity, int node_ct);
void *preflow_push_free(PreflowPush *p);

#define calloc_labels(p) node_array_calloc(p->node_ct)
#define calloc_flow(p) edge_array_calloc(p->node_ct)

int max_flow_reduced_caps(PreflowPush *p, int *flow, int *labels,
  int source, int sink);

#endif /* PREFLOW_PUSH */
