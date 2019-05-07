#ifndef TEST_HELPER_NETS_H
#define TEST_HELPER_NETS_H

void set_majority_net_no_cycles(int *majority, int node_ct);
void set_majority_net_partial_no_cycles(int *majority, int node_ct);
void set_majority_net_one_cycle_embedded(int *majority, int node_ct);
void set_majority_net_multi_cycle_embedded(int *majority, int node_ct);
void set_majority_net_two_embedded_cycles(int *majority, int node_ct);
void set_majority_tarjan_example(int *majority, int node_ct);

void set_preference_net_1(int *preference_graph, int node_ct);

#endif
