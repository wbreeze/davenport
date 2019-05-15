#include <cutter.h>
#include <limits.h>
#include "../src/network.h"
#include "../src/aggregate_solution.h"
#include "test_helper.h"

void test_aggregate_solution_create(void)
{
  const int node_ct = 12;
  AggregateSolution *asol = aggregate_solution_create(node_ct);
  edge_array_clear(asol->preference_graph, node_ct);
  node_array_clear(asol->aggregate_ranking, node_ct);
  cut_assert_equal_int(node_ct, asol->node_ct);
  cut_assert_equal_int(INT_MAX, asol->disagreement_ct);
  asol = aggregate_solution_destroy(asol);
  cut_assert_null(asol);
}

void test_aggregate_solution_one_solution(void)
{
  const int node_ct = 5;
  const int dct = INT_MAX - 1;
  AggregateSolution *asol = aggregate_solution_create(node_ct);

  int j1[] = { 5, 4, 2, 3, 1 };
  aggregate_solution_add_solution(asol, j1, node_ct, dct);

  assert_equal_int_array(j1, aggregate_solution_ranking(asol), node_ct);
  cut_assert_equal_int(dct, asol->disagreement_ct);

  aggregate_solution_destroy(asol);
}

void test_aggregate_solution_same_solution(void)
{
  const int node_ct = 5;
  const int dct = 3;
  AggregateSolution *asol = aggregate_solution_create(node_ct);

  int j1[] = { 5, 4, 2, 3, 1 };
  for (int i = 0; i < 4; ++i) {
    aggregate_solution_add_solution(asol, j1, node_ct, dct);
  }

  cut_assert_equal_int(dct, asol->disagreement_ct);
  assert_equal_int_array(j1, aggregate_solution_ranking(asol), node_ct);

  aggregate_solution_destroy(asol);
}

void test_aggregate_solution_with_ties(void)
{
  const int node_ct = 5;
  const int dct = 11;
  AggregateSolution *asol = aggregate_solution_create(node_ct);

  int j1[] = { 1, 2, 3, 4, 5 };
  aggregate_solution_add_solution(asol, j1, node_ct, dct);
  int j2[] = { 1, 2, 4, 3, 5 };
  aggregate_solution_add_solution(asol, j2, node_ct, dct);
  int j3[] = { 1, 3, 2, 4, 5 };
  aggregate_solution_add_solution(asol, j3, node_ct, dct);
  int j4[] = { 1, 3, 4, 2, 5 };
  aggregate_solution_add_solution(asol, j4, node_ct, dct);
  int j5[] = { 1, 4, 2, 3, 5 };
  aggregate_solution_add_solution(asol, j5, node_ct, dct);
  int j6[] = { 1, 4, 3, 2, 5 };
  aggregate_solution_add_solution(asol, j6, node_ct, dct);

  int result[] = { 1, 2, 2, 2, 5 };
  assert_equal_int_array(result, aggregate_solution_ranking(asol), node_ct);
  cut_assert_equal_int(dct, asol->disagreement_ct);

  aggregate_solution_destroy(asol);
}

void test_aggregate_solution_reset(void)
{
  const int node_ct = 5;
  const int dct = 1;
  AggregateSolution *asol = aggregate_solution_create(node_ct);

  int j1[] = { 1, 2, 3, 4, 5 };
  aggregate_solution_add_solution(asol, j1, node_ct, dct + 5);
  int j2[] = { 1, 2, 4, 3, 5 };
  aggregate_solution_add_solution(asol, j2, node_ct, dct + 4);
  int j3[] = { 1, 3, 2, 4, 5 };
  aggregate_solution_add_solution(asol, j3, node_ct, dct + 3);
  int j4[] = { 1, 3, 4, 2, 5 };
  aggregate_solution_add_solution(asol, j4, node_ct, dct + 2);
  int j5[] = { 1, 4, 2, 3, 5 };
  aggregate_solution_add_solution(asol, j5, node_ct, dct + 1);
  int j6[] = { 1, 4, 3, 2, 5 };
  aggregate_solution_add_solution(asol, j6, node_ct, dct);

  assert_equal_int_array(j6, aggregate_solution_ranking(asol), node_ct);
  cut_assert_equal_int(dct, asol->disagreement_ct);

  aggregate_solution_destroy(asol);
}
