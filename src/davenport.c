#include <stdlib.h>
#include "davenport.h"

struct Davenport {
  int foo;
  int bar;
};

Davenport *davenport_create() { return malloc(sizeof(struct Davenport)); }
void davenport_free(Davenport * d) { free(d); }
