#include "process.h"
process_t *processes[30];
uint32_t processes_count, current_pid;

void process_init() {
  processes_count = 0;
  current_pid = 0;
}

process_t *process_create(uint32_t *base_address) {

  process_t *process = kalloc(sizeof (process_t ) );

  process->pid = current_pid++;

  process->context.eax = 0;
  process->context.ecx = 0;
  process->context.ebx = 0;
  process->context.esp = 0;
  process->context.ebp = 0;
  process->context.esi = 0;
  process->context.edi = 0;
  process->context.eip = base_address;

  process->state = READY;
  process->base_address = base_address;

  processes[process->pid] = process;

  processes_count++;
}


