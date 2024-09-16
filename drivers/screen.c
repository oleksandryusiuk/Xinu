/** @file screen.c
 *
 * @brief Compact and simple VGA driver to control cursor, printing characters
 * and scrolling.
 *
 */

#include "screen.h"
#include "ports.h"
#include "../libc/util.h"

// Declaration of private functions
//
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

/**********************************************************
 *             Public Kernel API functions                *
 **********************************************************/

// Print character on given coordinates
//
void kprint_at(char *message, int col, int row) 
{
    // if position is negative, get CURRENT cursor position and print there.
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else 
    {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (message[i] != 0) 
    {
	// Print character and calculate the offset for next character 
    // as we want cursor pointing at next free cell                
        offset = print_char(message[i++], col, row, BLACK_ON_WHITE);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}
// Print at current cursor location.
//
void kprint(char *message) 
{
    kprint_at(message, -1, -1);
}

// Move cursor 1 char back
//
void kprint_backspace() 
{
  int offset = get_cursor_offset()-2;
  int row = get_offset_row(offset);
  int col = get_offset_col(offset);
  print_char(0x08, col, row, BLACK_ON_WHITE);
}


/**********************************************************
 *              Private kernel functions                  *
 **********************************************************/

 // Directly accesses video memory to print characters; If col/row negative,
 // print at current cursor location.
 //                                        
int print_char(char c, int col, int row, char attr) 
{
    uint8_t *vidmem = (uint8_t*) VIDEO_ADDRESS;
    if (!attr) attr = BLACK_ON_WHITE;

    /* Error control: print a red 'E' if the coords aren't right */
    if (col >= MAX_COLS || row >= MAX_ROWS) 
    {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') 
    {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } 
    else 
    {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLS * 2) 
    {
        int i;
        for (i = 1; i < MAX_ROWS; i++) 
            memory_copy(get_offset(0, i) + VIDEO_ADDRESS,
                        get_offset(0, i-1) + VIDEO_ADDRESS,
                        MAX_COLS * 2);

        /* Blank last line */
        char *last_line = get_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS;
        for (i = 0; i < MAX_COLS * 2; i++) 
        {
          last_line[i*2] = ' ';
          last_line[i*2+1] = BLACK_ON_WHITE;
        }
        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);
    return offset;
}
// Use the VGA ports to get the current cursor position
// 1. Ask for high byte of the cursor offset (data 14)
// 2. Ask for low byte (data 15)
//
int get_cursor_offset() 
{
    outb(REG_SCREEN_CTRL, 14);
    int offset = inb(REG_SCREEN_DATA) << 8; // High byte: << 8 
    outb(REG_SCREEN_CTRL, 15);
    offset += inb(REG_SCREEN_DATA);
    return offset * 2; // Position * size of character cell
}
// Similar to get_cursor_offset, but instead of reading we write data */
// 
//
void set_cursor_offset(int offset) 
{
    offset /= 2;
    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}
// Fills screen with empty characters and white background.
//
void clear_screen() 
{
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) 
    {
        screen[i*2] = ' ';
        screen[i*2+1] = BLACK_ON_WHITE;
    }
    set_cursor_offset(get_offset(0, 0));
}

// Functions to calculate current offsets
//
int get_offset(int col, int row) {return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }
