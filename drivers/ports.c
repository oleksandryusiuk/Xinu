#include "ports.h"
/** @file ports.c
 * 
 * @brief Compact driver to communicate with IO devices using functions
 * that may read/write a byte/word to an IO register using out/in assembly keywords.
 *
 */


// Reads byte from a specified register and returns it;
//
uint8_t inb(uint16_t port) 
{
  uint8_t result;
  __asm__("in %%dx , %%al" : "=a" (result) : "d" (port));
  return result;
}

// Send byte to register specified by address.
//
void outb(uint16_t port, uint8_t data) 
{
  __asm__("out %%al, %%dx" : : "a" (data), "d" (port));  
}

// Reads word from a specified register and returns it;
//
uint16_t inw(uint16_t port) 
{
  uint16_t result;
  __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
}

// Sends word to register specified by address.
//
void outw(uint16_t port, uint16_t data) 
{
  __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
