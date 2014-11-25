#ifndef BO_EXTRAS
#define B__EXTRAS
#include <string.h>
#include "bookorder.h"
#include "queue.h"

int hashInt(void* v);
int cmpKeyInt(void* v, void* w);
void FreeCustomer(void* _c);

int hashStr(void* v);
int cmpKeyStr(void* v, void* w);
void FreeQueue(void* _q);

#endif
