#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "ranking.h"
#include "solution_graph.h"

/*
 Default change callback is a no-op saves testing for NULL before calling.
*/
void sg_default_change(void *_c, int _u, int _v, int _dir) {};

SolutionGraph *solution_graph_create(int node_ct)
{
  SolutionGraph *sol = malloc(sizeof(SolutionGraph));

  sol->node_ct = node_ct;
  sol->solution = solution_array_calloc(node_ct);
  sol->set_point = 0;
  sol->edge_stack = edge_stack_calloc(node_ct);
  sol->change = &sg_default_change;

  return sol;
}

SolutionGraph *solution_graph_destroy(SolutionGraph *sol)
{
  free(sol->edge_stack);
  free(sol->solution);
  free(sol);
  return NULL;
}

void solution_graph_on_edge_change(SolutionGraph *sol,
  SolutionGraphEdgeChange *change, void *context)
{
  sol->change = change;
  sol->change_context = context;
}

/*
 This is for internal use. It assumes checks made by the function,
   "set_graph_add_edge()" and is called from there. In particular,
 - The opposite direction edge is not already set
 - This does no transitive updates
 This does update the record of added edges to support rollback.
*/
void sg_set_edge(SolutionGraph *sol, int u, int v)
{
  int edge_offset = RCI(u,v,sol->node_ct);
  if (sol->solution[edge_offset] == 0) {
    sol->solution[edge_offset] = 1;
    sol->edge_stack[sol->set_point++] = edge_offset;
    sol->change(sol->change_context, u, v, 1);
  }
}

int solution_graph_add_edge(SolutionGraph *sol, int u, int v)
{
  int set_point = sol->set_point;
  if (sol->solution[RCI(u,v,sol->node_ct)] == 0 &&
      sol->solution[RCI(v,u,sol->node_ct)] == 0) {
    sg_set_edge(sol, u, v);
    for (int w = 0; w < sol->node_ct; ++w) {
      if (sol->solution[RCI(v,w,sol->node_ct)] != 0) {
        sg_set_edge(sol, u, w);
      }
    }
    for (int t = 0; t < sol->node_ct; ++t) {
      if (sol->solution[RCI(t,u,sol->node_ct)] != 0) {
        for (int w = 0; w < sol->node_ct; ++w) {
          if (sol->solution[RCI(u,w,sol->node_ct)] != 0) {
            sg_set_edge(sol, t, w);
          }
        }
      }
    }
  }
  return set_point;
}

void solution_graph_rollback(SolutionGraph *sol, int set_point) {
  while (set_point < sol->set_point) {
    int edge_offset = sol->edge_stack[--sol->set_point];
    sol->solution[edge_offset] = 0;
    int u = ROW(edge_offset, sol->node_ct);
    int v = COL(edge_offset, sol->node_ct);
    sol->change(sol->change_context, u, v, -1);
  }
}

unsigned char solution_graph_has_edge(SolutionGraph *sol, int r, int c)
{
   return sol->solution[RCI(r,c,sol->node_ct)];
}

void solution_graph_rank_sort_items(SolutionGraph *sol,
  const int *topological_sort, int *ranking)
{
  rank_sorted_items(sol->solution, topological_sort, sol->node_ct, ranking);
}

void solution_graph_printl(SolutionGraph *sol, char *message)
{
  solution_array_printl(sol->solution, sol->node_ct, message);
}
