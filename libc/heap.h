#ifndef HEAP_H
#define HEAP_H
#include "../cpu/type.h"

extern uint32_t heap_base;
void heap_init();
int kalloc(int);
#endif
