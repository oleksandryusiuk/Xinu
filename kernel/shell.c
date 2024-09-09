// A primitive shell.

#include "shell.h"
#include "../drivers/keyboard.h"

void init_shell(){
  kprint("Welcome to Xinu. Type help for additional commands.");
  kprint("\n> ");
}

void user_input(char *input) {
  if(strcmp(input, "") == 1) {
    kprint("");
  }
  else if (strcmp(input, "HELP") == 1) {
    kprint("\nAvailable commands: help, halt, clear\n> ");
  }
  else if (strcmp(input, "HALT") == 1) {
    kprint("You have chosen to halt the cpu.");
    asm ("hlt");
  }
  else if (strcmp(input, "CLEAR") == 1) {
    clear_screen();
    kprint("> ");
  }  
  else {
      kprint("\nUnknown command.\n> ");
      return input;
  }
}

