#include <cutter.h>
#include "test_helper.h"
#include "../src/network.h"
#include "../src/tarjan.h"

struct ComponentCallback {
  unsigned char was_called;
  int next_id;
  int *components;
};

void component_callback(void *context, int *component, int component_sz)
{
  struct ComponentCallback *ccb = (struct ComponentCallback *)context;
  ccb->was_called = 1;
  ++ccb->next_id;
  for (int i = 0; i < component_sz; ++i) {
    ccb->components[component[i]] = ccb->next_id;
  }
}

void components_to_precedence(const int *components,
  int *precedence, int node_ct)
{
  for (int u = 0; u < node_ct; ++u) {
    for (int v = 0; v < node_ct; ++v) {
      if (u != v && components[u] != components[v]) {
        precedence[RCI(u,v,node_ct)] = 1;
      }
    }
  }
}

void test_tarjan_component_callback(void)
{
  int node_ct = 8;
  int *edges = edge_array_calloc(node_ct);
  struct ComponentCallback ccb;
  ccb.was_called = 0;
  ccb.next_id = 0;
  ccb.components = node_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);

  set_majority_net_two_embedded_cycles(edges, node_ct);

  Tarjan *t = tarjan_create(tarjan_default_edge_lookup, edges, node_ct);

  tarjan_set_component_callback(t, &component_callback, &ccb);
  cut_assert_equal_pointer(&component_callback, t->component_callback);
  cut_assert_equal_pointer(&ccb, t->component_callback_context);

  tarjan_identify_components(t, components);

  cut_assert_true(ccb.was_called);

  int *ccb_precedence = edge_array_calloc(node_ct);
  components_to_precedence(ccb.components, ccb_precedence, node_ct);
  int *tjn_precedence = edge_array_calloc(node_ct);
  components_to_precedence(components, tjn_precedence, node_ct);

  assert_equal_int_array(tjn_precedence, ccb_precedence, ECT(node_ct));

  free(tjn_precedence);
  free(ccb_precedence);
  t = tarjan_destroy(t);
  free(components);
  free(ccb.components);
  free(edges);
}
