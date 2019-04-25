#include <stdio.h>
#include "network.h"

void print_header(int node_ct)
{
  printf("%5s", ":/: ");
  for(int c = 0; c < node_ct; ++c)
  {
    printf("%3d ", c);
  }
  printf("\n");
}

void edge_array_print(const int *edges, int node_ct)
{
  print_header(node_ct);
  for(int r = 0; r < node_ct; ++r)
  {
    printf("%3d: ", r);
    for(int c = 0; c < node_ct; ++c)
    {
      printf("%3d ", edges[RCI(r,c,node_ct)]);
    }
    printf("\n");
  }
}

void edge_array_printl(const int *edges, int node_ct, char *label)
{
  printf("%s:\n", label);
  edge_array_print(edges, node_ct);
}

void node_array_print(const int *nodes, int node_ct)
{
  for(int i = 0; i < node_ct; ++i)
    printf("%3d ", nodes[i]);
  printf("\n");
}

void node_array_printl(const int *nodes, int node_ct, char *label)
{
  printf("%s:\n", label);
  node_array_print(nodes, node_ct);
}

void solution_array_print(const unsigned char *solution, int node_ct)
{
  print_header(node_ct);
  for(int r = 0; r < node_ct; ++r)
  {
    printf("%3d: ", r);
    for(int c = 0; c < node_ct; ++c)
    {
      printf("%3d ", solution[RCI(r,c,node_ct)]);
    }
    printf("\n");
  }
}

void solution_array_printl(const unsigned char *solution, int node_ct, char *label)
{
  printf("%s:\n", label);
  solution_array_print(solution, node_ct);
}
