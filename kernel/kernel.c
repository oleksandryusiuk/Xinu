/** @file main.c 
 *
 * @brief main execution file
 *
 */

#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/util.h"
#include "process.h"
#include "shell.h"
#include "../libc/heap.h"
#include "paging.h"


void main() 
{
  isr_install();
  irq_install();
  heap_init();
  paging_init();
  process_init();

  clear_screen();
  init_shell();
}  


