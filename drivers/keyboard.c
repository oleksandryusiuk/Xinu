/** @file keyboard.c
 *
 * @brief Keyboard driver that reads scancode from specified location, converts 
 * it into ASCII char and prints it on screen.
 *
 */

#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/function.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

// Read scancode from 0x60, handles Enter/Backspace and prints all other chars.
// 
static void keyboard_callback(registers_t regs) 
{
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = inb(0x60);
    if (scancode > SC_MAX) return;
    // Backspace handler
    if (scancode == BACKSPACE) 
    {
        backspace(key_buffer);
        kprint_backspace();
    }
    // Enter Handler
    else if (scancode == ENTER) 
    {
        kprint("\n");
        user_input(key_buffer);
        key_buffer[0] = '\0';
    }
    // Print any other character;
    else
    {
        char letter = sc_ascii[(int)scancode];
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

// Maps keyboard_callback to be handler function for IRQ1.
//
void init_keyboard() 
{
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
