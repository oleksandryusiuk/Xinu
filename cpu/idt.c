/** @file idt.c
 * 
 * @brief contains functions to set and configure IDT gates
 *
 */


// Interrupt descriptor table - is a special complex datastructure,              
// that holds all data about interrupts and used by processor to know where the specific ISRs are. 
// single IDT entry is called gate.                                                                
//
#include "idt.h"
#include "../libc/util.h"

// declaring array of structures of size IDT_ENTRIES (256). 
//
idt_gate_t idt[IDT_ENTRIES];

// idt_reg will be loaded using assembly lidt instruction
// 
idt_register_t idt_reg;

// Sets all IDT gate data
//
void set_idt_gate(int n, uint32_t handler) 
{
  idt[n].low_offset = low_16(handler);
  idt[n].sel = KERNEL_CS;
  idt[n].always0 = 0;
  idt[n].flags = 0x8E;
  idt[n].high_offset = high_16(handler);
}

// Loads IDT using lidtl directive
//
void set_idt() 
{
  idt_reg.base = (uint32_t) &idt;
  idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

  asm volatile("lidtl (%0)" : : "r" (&idt_reg));
}
