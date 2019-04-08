#ifndef DAVENPORT_H
#define DAVENPORT_H

typedef struct Davenport Davenport;

Davenport *davenport_create();
void davenport_free(Davenport * d);

#endif
