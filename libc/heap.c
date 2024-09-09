#include "heap.h"

uint32_t heap_base;

void heap_init() {
  heap_base = 0x100000;
}

/* All of our memory for a processes will be allocated from address 0x100000. */
/* This function takes size of an object in bytes, sets its address base to   */
/* current heap base, and increases base for the next process to be based     */
/* just after previous process.                                               */

int kalloc(int bytes) {
  uint32_t new_object_address = heap_base;
  heap_base += bytes;
  return new_object_address;
}
