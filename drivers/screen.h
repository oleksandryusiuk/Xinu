/** @file screen.h
 * 
 * 
 *
 */
 
#ifndef SCREEN_H
#define SCREEN_H
#include "../cpu/type.h"
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define BLACK_ON_WHITE 0xf0
#define RED_ON_WHITE 0xf4

// VGA I/O ports

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

// declaration of public kernel functions

void kprint_backspace();
void clear_screen();
void kprint_at(char *message, int col, int row);
void kprint(char *message);
#endif
