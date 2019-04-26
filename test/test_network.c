#include <cutter.h>
#include "../src/network.h"

void test_network_indexing(void)
{
  int node_ct = 12;

  int r = 3, c = 4;
  int index = RCI(r,c,node_ct);
  cut_assert_equal_int(r, ROW(index,node_ct));
  cut_assert_equal_int(c, COL(index,node_ct));

  r = c = 0;
  index = RCI(r,c,node_ct);
  cut_assert_equal_int(r, ROW(index,node_ct));
  cut_assert_equal_int(c, COL(index,node_ct));

  r = 11; c = 0;
  index = RCI(r,c,node_ct);
  cut_assert_equal_int(r, ROW(index,node_ct));
  cut_assert_equal_int(c, COL(index,node_ct));

  r = 0; c = 11;
  index = RCI(r,c,node_ct);
  cut_assert_equal_int(r, ROW(index,node_ct));
  cut_assert_equal_int(c, COL(index,node_ct));

  r = c = 11;
  index = RCI(r,c,node_ct);
  cut_assert_equal_int(r, ROW(index,node_ct));
  cut_assert_equal_int(c, COL(index,node_ct));

  r = c = 6;
  index = RCI(r,c,node_ct);
  cut_assert_equal_int(r, ROW(index,node_ct));
  cut_assert_equal_int(c, COL(index,node_ct));

  r = 4; c = 3;
  index = RCI(r,c,node_ct);
  cut_assert_equal_int(r, ROW(index,node_ct));
  cut_assert_equal_int(c, COL(index,node_ct));
}
