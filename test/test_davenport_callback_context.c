#include <cutter.h>
#include <string.h>
#include <stdio.h> // printf
#include "../src/davenport.h"
#include "../src/network.h"
#include "test_davenport_callback_context.h"

void handle_solution(void *context, int *ranking, int node_ct,
  int disagreement_ct)
{
  CallbackContext *cbx = (CallbackContext *)context;
  cbx->last_solution = ranking;
  Davenport *dv = cbx->dv;
  if (disagreement_ct == cbx->expected_disagreements) {
    ++cbx->seen_solution_ct;
    unsigned char match = (0 == cbx->valid_solution_ct);
    int next_valid = 0;
    while (match == 0 && next_valid < cbx->valid_solution_ct) {
      int cmp = memcmp(cbx->valid_solutions[next_valid], ranking, NSZ(node_ct));
      if (cmp == 0) match = 1;
      ++next_valid;
    }
    cut_assert_true(match,
      cut_message("Solution matches expected valid solution"));
  }
  if (disagreement_ct < cbx->expected_disagreements) {
    cut_fail("Have %d disagreements; best expected is %d\n", disagreement_ct,
      cbx->expected_disagreements);
  }
}
