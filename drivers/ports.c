#include "ports.h"

// (in byte) reads byte from specified port.
uint8_t inb(uint16_t port) {
  // declares 1 byte variable result; because io requests are too
  // low level for C, we must use inline assembly
  // basically this function requests byte from device port using 'in'
  // instruction, where dx is the port, and al is the result 
  // (the value) of the io device register.
  uint8_t result;
  __asm__("in %%dx , %%al" : "=a" (result) : "d" (port));
  return result;
}

void outb(uint16_t port, uint8_t data) {
  // sends 'data' byte to io device by address (port) using 'out' instruction
  __asm__("out %%al, %%dx" : : "a" (data), "d" (port));  
}

uint16_t inw(uint16_t port) {
  // request word from io device and saves in result (al)
  uint16_t result;
  __asm__("out %%al, %%dx" : "=a" (result) : "d" (port));
}

void outw(uint16_t port, uint16_t data) {
  // sends 'data' word to io device specified by address (port) using 'out' instuction
  __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
