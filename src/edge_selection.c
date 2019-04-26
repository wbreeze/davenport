#include "edge_selection.h"

#define value_at(e,a,i) e[a[i]]
#define swap(a,i,j) { int t=a[i]; a[i]=a[j]; a[j]=t; }

/*
 This is quicksort with 3-way partitioning copied from
 www.cs.princeton.edu/~rs/talks/QuicksortIsOptimal.pdf
 and modified for:
 - the indirection of value lookup.
 - reverse sort
*/
void quicksort(const int *e, int *a, int l, int r)
{
  if (r <= l) return;
  int i = l - 1, j = r, p = l - 1, q = r;
  int v = value_at(e,a,r);
  for(;;) {
    while (v < value_at(e,a,++i));
    while (value_at(e,a,--j) < v) if (j == l) break;
    if (i >= j) break;
    swap(a,i,j);
    if (value_at(e,a,i) == v) { p++; swap(a,p,i); }
    if (v == value_at(e,a,j)) { q--; swap(a,j,q); }
  }
  swap(a,i,q);
  j = i-1; i = i+1;
  for (int k = l; k <= p; k++, j--) swap(a,k,j);
  for (int k = r; k > q; k--, i++) swap(a,i,k);
  quicksort(e, a, l, j);
  quicksort(e, a, i, r);
}

void sort_edge_selection(const int *edges, int *selection, int select_ct)
{
  quicksort(edges, selection, 0, select_ct-1);
}
