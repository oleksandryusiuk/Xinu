#ifndef PROCESS_H
#define PROCESS_H
#include "../cpu/type.h"
typedef enum { READY, RUNNING } process_state_t;

typedef struct process_context {
  int eax, ecx, edx, ebx, esp, ebp, esi, edi, eip;
} process_context_t;

typedef struct process {
  uint32_t pid;
  process_context_t context;
  process_state_t state;
  uint32_t *base_address;
} process_t;

extern process_t *processes[30];
extern uint32_t processes_count, current_pid;

void process_init();
process_t *process_create(uint32_t *);
#endif
